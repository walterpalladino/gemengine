# GemEngine

GemEngine is a 2D graphic engine based on SDL2.



## Why GemEngine

With GemEngine I try to write a base to create graphic portable applications.
To accomplish that I try to use as much standard libraries as possible, like SDL2 and a general use language like C++.

## Features covered so far

This is a pretty new project so I'm covering so far:

 - Physical and Virtual screen allowing to create retro like pixelation effects.
 - Text Console with methods to locate cursor on console and write bitmapped fonts.
 - Image load
 - Animated Sprites
 - Wired Triangles
 - Filled Triangles (with clipping)


## Whats comes next
I hope a lot more

 

## Mac OS
For Mac OS are required some steps based on the deployment you choose.
I added the package command to the makefile to create an application bundle which includes the Frameworks and other Resources required to run the app.
You can still run the binary accessing the relative folders including those resources if you choose.
For the binary you need to enable access to the system Frameworks using the command:
install_name_tool -add_rpath /Library/Frameworks ./bin/GemEngine

### Edited using

https://stackedit.io/app#