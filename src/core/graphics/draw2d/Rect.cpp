#include "core/graphics/draw2d/Rect.h"

RectInt::RectInt()
{
    this->left = 0;
    this->right = 0;
    this->top = 0;
    this->bottom = 0;
}

RectInt::RectInt(int left, int right, int top, int bottom)
{
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
}
