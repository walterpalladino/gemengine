#pragma once

#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "math/Vector2d.h"

using namespace std;

enum MouseButton
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler *Instance()
    {
        if (instance == 0)
        {
            instance = new InputHandler();
        }

        return instance;
    }

    void Init();
    bool Update();
    void Clean();

    // Keyboard //

    unordered_map<SDL_Keycode, bool> keymapPrev;
    unordered_map<SDL_Keycode, bool> keymap;
    bool IsKeyDown(SDL_Scancode key);
    bool WasKeyPressed(SDL_Scancode key);
    bool WasKeyReleased(SDL_Scancode key);

    // Mouse //

    bool GetMouseButtonState(int buttonNum)
    {
        return mouseButtonStates[buttonNum];
    }

    Vector2d *GetMousePosition()
    {
        return mousePosition;
    }

    void Reset();

private:
    InputHandler() {}
    ~InputHandler() {}

    static InputHandler *instance;

    // Keyboard //
    const Uint8 *keystates;

    void OnKeyDown(SDL_Event &event);
    void OnKeyUp(SDL_Event &event);

    // Mouse //

    std::vector<bool> mouseButtonStates;

    Vector2d *mousePosition;

    void OnMouseMove(SDL_Event &event);
    void OnMouseButtonDown(SDL_Event &event);
    void OnMouseButtonUp(SDL_Event &event);
};

// typedef InputHandler _InputHandler;