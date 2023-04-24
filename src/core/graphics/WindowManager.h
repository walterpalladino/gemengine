#pragma once

#include "core/graphics/draw2d/Rect.h"

class WindowManager
{
public:
    static WindowManager *Instance()
    {
        if (instance == 0)
        {
            instance = new WindowManager();
        }
        return instance;
    }

private:
    WindowManager() {}
    ~WindowManager() {}

    static WindowManager *instance;

public:
    RectInt boundaries;
};
