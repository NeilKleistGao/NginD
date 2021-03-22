# NginD
[![Documentation Status](https://readthedocs.org/projects/ngind-doc/badge/?version=latest)](https://ngind-doc.readthedocs.io/en/latest/?badge=latest)

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
### 0.7
+ [x] Encrypt System
+ [x] Compress

### 0.8
+ [ ] Box2D Support

### 0.9
+ [ ] Tiled Map
+ [ ] Screen Adaptor

### 1.0(?)
+ [ ] Package Tools
+ [ ] Saving Game Files
+ [ ] Full Documentation

## Dependent Libraries
### Engine Dependent Libraries
+ [GLEW 2.1.0](https://github.com/nigels-com/glew)
+ [GLFW 3.3.2](https://www.glfw.org/)
+ [RapidJSON 1.1.0](http://rapidjson.org/)
+ [FreeType 2.10.3](https://www.freetype.org/index.html)
+ [SOIL2 1.20](https://github.com/SpartanJ/SOIL2)
+ [glm 0.9.9.8](https://glm.g-truc.net/0.9.9/index.html)
+ [Lua 5.4.2](https://www.lua.org/)
+ [Lua Bridge 2.6](https://github.com/vinniefalco/LuaBridge)
+ [SoLoud 20200207](http://sol.gfxile.net/soloud/index.html)
+ [Aseprite 1.2.25dev](http://www.aseprite.org/)
+ [Snappy 1.1.8](https://github.com/google/snappy)

### Documentation Libraries
+ [Sphinx 2.2.0](https://www.sphinx.org.cn/)

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
+ IDE: CLion 2020.2, WebStorm 2020.2

The engine will support for Windows and MacOS later.

## Special Acknowledgements
+ Humphrey_Yang
+ riceblast
+ JzJerry
+ PtCu
+ youyadefeng
+ yxlei
+ magwer
+ Chin
+ sonikk
+ AlohaWorld
+ mxx