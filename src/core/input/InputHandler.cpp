#include <iostream>

#include "core/input/InputHandler.h"

InputHandler *InputHandler::instance = 0;

void InputHandler::Init()
{
    for (int i = 0; i < 3; i++)
    {
        mouseButtonStates.push_back(false);
    }

    mousePosition = new Vector2d(0, 0);
}

bool InputHandler::Update()
{
    SDL_Event event;

    keymapPrev = keymap;
    // keymap.clear();

    bool quit = false;

    // while (SDL_PollEvent(&event))
    while (SDL_WaitEventTimeout(&event, 1))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            //_Game::Instance()->quit();
            quit = true;
            break;

        case SDL_KEYDOWN:
            OnKeyDown(&event);
            break;

        case SDL_KEYUP:
            OnKeyUp(&event);
            break;

        case SDL_MOUSEMOTION:
            OnMouseMove(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            OnMouseButtonDown(event);
            break;

        case SDL_MOUSEBUTTONUP:
            OnMouseButtonUp(event);
            break;

        default:
            break;
        }
    }

    return quit;
}

void InputHandler::OnMouseButtonDown(SDL_Event &e)
{
    if (e.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates[LEFT] = true;
        // std::cout << "Left Mouse Button Pressed." << std::endl;
    }
    else if (e.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates[MIDDLE] = true;
        // std::cout << "Middle Mouse Button Pressed." << std::endl;
    }
    else if (e.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates[RIGHT] = true;
        // std::cout << "Right Mouse Button Pressed." << std::endl;
    }
}

void InputHandler::OnMouseButtonUp(SDL_Event &e)
{
    if (e.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates[LEFT] = false;
        // std::cout << "Left Mouse Button Released." << std::endl;
    }
    else if (e.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates[MIDDLE] = false;
        // std::cout << "Middle Mouse Button Released." << std::endl;
    }
    else if (e.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates[RIGHT] = false;
        // std::cout << "Right Mouse Button Released." << std::endl;
    }
}

void InputHandler::OnMouseMove(SDL_Event &e)
{
    mousePosition->x = e.motion.x;
    mousePosition->y = e.motion.y;

    // std::cout << "Mouse position = x: " << mousePosition->x << ", y:" << mousePosition->y << std::endl;
}

void InputHandler::Reset()
{
    for (int i = 0; i < mouseButtonStates.size(); i++)
    {
        mouseButtonStates[i] = false;
    }
}

void InputHandler::OnKeyDown(SDL_Event *event)
{
    if (keymap.count(event->key.keysym.sym) != 0)
    {
    }
    keymap[event->key.keysym.sym] = true;
    // std::cout << "Key Pressed: " << SDL_GetKeyName(event->key.keysym.sym) << std::endl;
}

void InputHandler::OnKeyUp(SDL_Event *event)
{
    if (keymap.count(event->key.keysym.sym) != 0)
    {
    }
    keymap[event->key.keysym.sym] = false;
    // std::cout << "Key Released: " << SDL_GetKeyName(event->key.keysym.sym) << std::endl;
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{

    return (keymap.count(SDL_GetKeyFromScancode(key)) != 0) && (keymap[SDL_GetKeyFromScancode(key)] == true);

    if (keystates != 0)
    {
        if (keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool InputHandler::WasKeyPressed(SDL_Scancode key)
{
    return (keymapPrev.count(key) == 0) && (keymap.count(key) != 0);
}

void InputHandler::Clean()
{
}
