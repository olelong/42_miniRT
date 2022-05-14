# 42_miniRT

### The objective of the program is to model images according to the raytracing protocol.

These images must represent a scene, seen from a defined angle and containing simple 
geometrical objects, each with objects, each with its own lighting system.

This project uses the MinilibX, the goal was to implement at least 3 simple geometric 
objects such as plane, sphere, Cylinder and to be able to apply transformations to objects,
lights and camera: translation and rotation.


### An example of a simple scene with multi-objects:

![origin](./img/origin.png)

### How does it works :

#### To launch the program you can :
Type the command ``` Make ```
Launch the executable ``` ./minirt ``` followed by a .rt file like ```maps/home.rt```

-> The .rt files are files that are used to configure scenes.
There are some examples of configuration files .rt in the map folder but you can configure your own.
(See how below)

#### To quit the scene you can :
Press the ESC key or click on the red cross in the window to close the window and exit
the program program properly.

### Other examples of maps :

![home](./img/home.png)
![moon](./img/moon.png)
![ballWall](./img/ballWall.png)
