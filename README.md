# Boids technique in C language
_This is a C project to emulate flocks, hordes or other type of aggregation groups._


# How To Create .Exe

Open your terminal and go to the directory path then copy and paste this string:

```
clang -I SDL2-2.0.10\include\ -L SDL2-2.0.10\lib\x64\ -l SDL2 -o main.exe *.c
```

####  You must have clang by @LLVM in ur computer, [you can find it here].(https://releases.llvm.org/)


# How It Works
While you have created your .exe file, just open it and left click on random points into the game window. This will create random assets that float around the world. While two assets meet, they will start to create a group. 

To modify parameters to have different effects you have to go into **boids.c** file and modify this parameters:
```
    boid_obj->alignment_radius = 150.0f;
    boid_obj->cohesion_radius = 100.0f;
    boid_obj->separation_radius=70.0f;
    boid_obj->alignment_weight = 0.5f;
    boid_obj->cohesion_weight = 0.2f;
    boid_obj->separation_weight = 0.9f;
```