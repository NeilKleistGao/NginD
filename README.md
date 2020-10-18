# NginD
A game engine for 2D pixel game powered by C++ (自家用). 

## Features
+ Drag spirits to decorate your scenes
+ Import images, music, animations from other software
+ Use components to implement your games
+ Encapsulated box2D, OpenGL and so on
+ Support for Lua as script language
+ Designed classes for map, dialog, object and so on
+ Encrypt your resources
+ AI modules for your NPC
+ Provide interfaces for advanced researches in game AI
+ ...

## TODO List
+ [x] Serialization
+ [ ] Input System
+ [ ] OpenGL Interface
+ [x] Resources Management
+ [x] Log System
+ [x] Garbage Collection
+ [ ] Basic Components
+ [x] Timer System

## Dependent Library
+ [OpenGL 4.6(using glad)](https://glad.dav1d.de/)
+ [GLFW 3.3.2](https://www.glfw.org/)
+ [libpng 1.6.34](http://www.libpng.org/pub/png/libpng.html)
+ [C++ Boost 1.74.0](https://www.boost.org/)
+ [RTTR 0.9.6](https://www.rttr.org/)
+ [RapidJSON 1.1.0](http://rapidjson.org/)
+ [FreeType 2.10.3](https://www.freetype.org/index.html)

Thanks for these open source developers!

## Code Style Guide
We'll use Google's C++ style guild:
+ [Google Style Guides](https://github.com/google/styleguide)

However, here are some exceptions:
+ The first alphabet of function name should be lower case
+ Tabs should be used, and should be equivalent to 4 spaces. There is no space before the keywords `public`, `private` and `protected`
+ The underline after the name of class members should be moved to the front of the name
+ Stream will be used to serialize/deserialize/type conversion

## Code Environment
+ OS: Ubuntu 18.04.4 LTS
+ Compiler: CMake 3.15.3(C++17)
+ IDE: CLion 2019.3.2

The engine will support for Windows and MacOS later.

## Acknowledgements
+ Humphrey_Yang
+ riceblast
+ JzJerry
+ PtCu