<iframe width="560" height="315" src="https://www.youtube.com/embed/vvXfCGgURfA?si=nd4CaToV1h-eD3R4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

## Inspiration
I wanted to try making something like the shoulder cannon from a predator but I didn’t know how I would attach it to my shoulder so I receded to a simpler project: a rubber band turret. After researching how I can shoot rubber bands I found [this](https://hackaday.com/2019/02/13/palm-sized-gatling-gun-has-32-mini-elastics-with-your-name-on-them/) design which allows me to turn rotational movement into continuous shooting of rubber bands.

## What it does
I programmed an arduino to control 3 different servos which are part of the turret. The individual servos control the pitch, yaw, and shooting of the turret The turret can be controlled using an app I created for my phone. The turret fits 5 elastic bands before it needs to be reloaded. The turret can also be controlled by a bluetooth glove I created earlier as a different project. You can view the glove as another project on my Devpost account.

## How I built it
I started with designing the shooting mechanism based on the design previously mentioned. I modified 3D models from the internet to fit the servos into my design since I didn’t have the resources to design the servo parts myself. I 3D printed the parts and started working on programming and creating the circuit for the arduino. After I was able to create a functioning turret controlled by the arduino, I created a bluetooth app to control the turret using Unity (since I had previously purchased a BLE plugin for it).

## Challenges I ran into
The largest challenge I ran into during this project was designing a barrel with notches that could hold the rubber bands securely while also being able to easily release the rubber bands when they needed to be shot. I have enough 3D printed barrels to stack them into a tower over 1m high.

## Accomplishments that I’m proud of
I’m proud of being able to design something as functional as the turret because it was my first time designing a mechanism. I also designed it in Blender which is mainly a 3D modeling/rendering software but It would have probably been better to use an actual CAD software.

## What I learned
This is the first time I tried programming servos using arduino. The servos rotate “instantly” to a target position but I learned how to make them interpolate smoothly to a target position.
