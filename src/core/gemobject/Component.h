#pragma once

enum class ComponentType : int
{
    Image = 1,
    Text = 2,
    Sprite = 3,
    Parallax = 4,
    Sound = 5,
    Collider = 6
};

class Component
{
public:
    bool enabled = true;

public:
    virtual ComponentType GetType() = 0;
    virtual void Update(float time) = 0;
};
