# 1_course_2017_project
PSEUDO 3D game engine written with C and SDL2
![sreenshot](https://drive.google.com/uc?id=1T0NFMuxwm_5ABGqYJu94TciIU12qWrML)
=======

## How to build
- building:
```bash
$ git clone https://github.com/F1NYA/1_course_2017_project.git
$ cd 1_course_2017_project
$ make
```

## Run project
- running:
```bash
$ cd bin
$ ./progbase3
```

## Change project settings

You can change macroses in ```include/macros.h```
```c
#define W 2048    // Width
#define H 1080    // Height

#define EyeH  6   // Camera Height
#define DuckH 2.5 // On "duck" camera height
#define HeadM 1
#define KneeH 2
#define hfov (0.73f*H)
#define vfov (.2f*H)

#define NEAR_Z 1e-4f
#define FAR_Z  5
#define NEAR_X 1e-5f
#define FAR_X 20.f
```
