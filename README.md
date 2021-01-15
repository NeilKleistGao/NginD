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
### 0.3
+ [ ] Audio System
+ [ ] Button Component
+ [ ] I18N

### 0.4
+ [ ] Visual Editor

### 0.5
+ [ ] Simple Animation System
+ [ ] Animation Editor Support

### 0.6
+ [ ] Tiled Map Support

### 0.7
+ [ ] Textbox Component
+ [ ] Encrypt System

### 0.8
+ [ ] Package and Compress

### 0.9
+ [ ] Advanced Sprite Support

### 0.10
+ [ ] Advanced Animation System
+ [ ] More Editor Support

### 0.11
+ [ ] Windows Version

### 1.0
+ [ ] Full Render Interfaces

## Dependent Libraries
### Engine Dependent Libraries
+ [GLEW 2.1.0](https://github.com/nigels-com/glew)
+ [GLFW 3.3.2](https://www.glfw.org/)
+ [C++ Boost 1.74.0](https://www.boost.org/)
+ [RapidJSON 1.1.0](http://rapidjson.org/)
+ [FreeType 2.10.3](https://www.freetype.org/index.html)
+ [SOIL2 1.20](https://github.com/SpartanJ/SOIL2)
+ [glm 0.9.9.8](https://glm.g-truc.net/0.9.9/index.html)
+ [Lua 5.4.2](https://www.lua.org/)
+ [Lua Bridge 2.6](https://github.com/vinniefalco/LuaBridge)

### Editor Dependent Libraries
+ [electron 10.1.5](https://www.electronjs.org/)

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