#pragma once

// #include	<windows.h>
// #include	<windowsx.h>

// #include <stdio.h>

// #include	"../Graphics/CanvasGL.h"

// #include	"Point2d.h"
// #include	"Maths/Vector3d.h"

struct Vertex3d
{
	/*
		GLfloat		local[3] ;
		GLfloat		world[3] ;
		GLfloat		camera[3] ;
		GLfloat		screen[2] ;
	*/
	float local[3];
	float world[3];
	float camera[3];
	float screen[2];
};
