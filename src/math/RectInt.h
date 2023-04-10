
#pragma once

struct RectInt
{
public:
	int x,
		y,
		w,
		h;

	RectInt(){};
	RectInt(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};
