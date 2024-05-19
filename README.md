# Deps
bear, OpenGL libraries (glew, glfx), clang, stb (stb_image)

# Build System

I am using a simple makefile. It uses ./lib/ as libraries and compiles them if needed. Use just 'make' or 'make regular_compile' commands. (the regular_compile does not use bear).

# Code

The main execution of a program contains in a WindowClass in exec member function. Currently it supports only rotating an object and moving the camera back and forth. Textures on models are not supported.

# Current known bugs:
- For some reason, some polygons are not being drawn. It could be possibly because of bad implementation of 'Mesh' class
or bad object files.
- There are cases when shaders do not draw polygons for any reason. I didn't implement shaders in a good fashion described on https://developer.download.nvidia.com/SDK/10/direct3d/Source/SolidWireframe/Doc/SolidWireframe.pdf
- Edges of polygons are drawn in such a way that when you get further away from the model, they occupy more space of a triagnle.

# Current status

Unfinished.

# Contacts:
If something fails to compile or you have any questions about the project: telegram: @HenkinLeven