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

### How to create a file .rt:
To create a config file, you need at least an ambient light A which contains information like its
type A, its brightness [0.0,1.0] and its color [0,255].
Then you can add other elements, that is :
##### - A camera C followed by its coordinates, its 3D orientation vector [-1,1] and its field of view.
##### - A light L followed by its coordinates, its luminosity [0.0,1.0], and its color [0,255].
- As many objects as you want it to be :
##### cylinders cy :
Followed by its coordinates x,y,z, its orientation vector 3d [-1,1] for each axis x,y,z, 
its diameter,its height and its Color R,G,B [0,255].
##### spheres sp :
Followed by its coordinates, diameter and color [0,255].
##### pl planes :
Followed by its coordinates, its 3d orientation vector and its color [0,255].

![example](./img/example.png)

### Other examples of maps :

![home](./img/home.png)
![moon](./img/moonv2.png)
![ballWall](./img/ballWall.png)
