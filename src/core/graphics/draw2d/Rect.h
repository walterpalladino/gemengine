#pragma once

#include <ostream>

using namespace std;

struct RectInt
{

    int left;
    int right;
    int top;
    int bottom;

    RectInt();
    RectInt(int left, int top, int right, int bottom);

    friend ostream &operator<<(ostream &os, const RectInt &rect);
};