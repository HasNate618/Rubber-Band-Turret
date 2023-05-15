#include <ArduinoBLE.h>
#include <Servo.h>

BLEService service("58e19b7f-f5cc-469b-8377-542e89076a30");  // User defined service
BLEStringCharacteristic inputCharacteristic("ab2a89e6-b7c1-444c-a9b6-e8a304e1a447", BLERead | BLEWrite, 20);

String characteristicValue;
String datas[3] = { "90", "90", "0" };

Servo pitchServo, yawServo, barrelServo;
float pitch = 90, pitchPrev = 90;
float yaw = 90, yawPrev = 90;
int barrelAngle = 180;
const int minAngle = 0;
const int maxAngle = 180;

void setup() {
  Serial.begin(9600);

  // initialize servos
  pitchServo.attach(2);
  yawServo.attach(3);
  barrelServo.attach(4);
  pitchServo.write(pitch);
  yawServo.write(yaw);
  barrelServo.write(barrelAngle);

  // initialize the BLE hardware
  pinMode(LED_BUILTIN, OUTPUT);  // initialize the built-in LED pin

  if (!BLE.begin()) {  // initialize BLE
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Turret");      // Set name for connection
  BLE.setAdvertisedService(service);               // Advertise service
  service.addCharacteristic(inputCharacteristic);  // Add characteristic to service
  BLE.addService(service);                         // Add service
  inputCharacteristic.writeValue("0,0,0");

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
  delay(1000);
}

void loop() {
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central MAC: ");
    // print the central's BT address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      // keep looping while connected
      //Retrieve data
      int length = inputCharacteristic.valueLength();
      char bytes[length];
      inputCharacteristic.readValue(bytes, length);
      String data(bytes, length);

      // parse the data into an array
      parseString(data, ',');

      if (datas[2] == "1") {
        shoot();
      }
      else {
        updateServos();
      }
    }

    // when the central disconnects, turn off the LED:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());

    // Home servos
    yawServo.write(90);
    pitchServo.write(90);
    barrelServo.write(180);
  }
}

void updateServos() {
  float targetYaw, targetPitch;
  targetYaw = datas[0].toFloat();
  targetPitch = datas[1].toFloat();

  yaw = (targetYaw * 0.08) + (yawPrev * 0.92);
  pitch = (targetPitch * 0.08) + (pitchPrev * 0.92);
  yawPrev = yaw;
  pitchPrev = pitch;

  if (abs(pitch - targetPitch) > 2){ 
    pitchServo.write(pitch);
  }
  if (abs(yaw - targetYaw) > 2) {
    yawServo.write(yaw);
  }
  Serial.println("Target Pitch: " + String(targetPitch));
  Serial.println("Target Yaw: " + String(targetYaw));  
  Serial.print(pitch);
  Serial.print(",");
  Serial.println(yaw);
  delay(10);
}

void shoot() {
  barrelAngle -= 30;

  if (barrelAngle > maxAngle) {
    barrelAngle = maxAngle;
  }
  else if (barrelAngle < minAngle) {
    barrelAngle = minAngle;
  }

  Serial.println("Shot: " + String(barrelAngle));
  barrelServo.write(barrelAngle);
  delay(400);

  if (barrelAngle == minAngle) {
    Serial.println("Reloading...");
    barrelAngle = maxAngle;
    barrelServo.write(barrelAngle);
    delay(1000);
  }
}

void parseString(String str, char del) {
    // declaring temp string to store the curr "word" upto del
    String temp = "";
    int counter = 0;
   
    for(int i=0; i<str.length(); i++) {
      // If current char is not delimiter, then append it to the current "word", otherwise
      // you have completed the word, print it, and start a new word.
      if(str[i] != del) { 
          temp += str[i];
      }
      else {
        datas[counter] = temp;
        temp = "";
        counter++;
      }
    }
    datas[counter] = temp;
    temp = "";
    counter++;
}