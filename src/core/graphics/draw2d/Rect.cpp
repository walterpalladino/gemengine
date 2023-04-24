#include "core/graphics/draw2d/Rect.h"

RectInt::RectInt()
{
    this->left = 0;
    this->right = 0;
    this->top = 0;
    this->bottom = 0;
}

RectInt::RectInt(int left, int top, int right, int bottom)
{
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
}

ostream &operator<<(ostream &os, const RectInt &rect)
{
    os << rect.left << '/' << rect.top << '/' << rect.right << '/' << rect.bottom;
    return os;
}
