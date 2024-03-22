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

    // keymapPrev = keymap;
    //  keymap.clear();

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
    keymap[event->key.keysym.sym] = true;
    keymapPrev[event->key.keysym.sym] = false;
    // std::cout << "Key Pressed: " << SDL_GetKeyName(event->key.keysym.sym) << " key : " << event->key.keysym.sym << " scancode : " << SDL_GetScancodeFromKey(event->key.keysym.sym) << std::endl;
}

void InputHandler::OnKeyUp(SDL_Event *event)
{
    keymapPrev[event->key.keysym.sym] = true;
    keymap[event->key.keysym.sym] = false;
    // std::cout << "Key Released: " << SDL_GetKeyName(event->key.keysym.sym) << " key : " << event->key.keysym.sym << " scancode : " << SDL_GetScancodeFromKey(event->key.keysym.sym) << std::endl;
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
    // std::cout << "WasKeyPressed : " << key << std::endl;
    // std::cout << "keymapPrev.count(key) : " << keymapPrev.count(key) << std::endl;
    // std::cout << "keymap.count(key) : " << keymap.count(key) << std::endl;

    // return (keymapPrev.count(SDL_GetKeyFromScancode(key)) == 0) && (keymap.count(SDL_GetKeyFromScancode(key)) != 0);

    int keyCode = SDL_GetKeyFromScancode(key);
    // std::cout << "WasKeyPressed : " << keyCode << " keymapPrev.count(key) : " << keymapPrev.count(keyCode) << " keymap.count(key) : " << keymap.count(keyCode) << std::endl;

    bool wasPressed = ((keymapPrev.count(keyCode) == 0) || (keymapPrev[keyCode] == false)) && (keymap.count(keyCode) != 0) && (keymap[keyCode] == true);

    keymapPrev[keyCode] = true;

    return wasPressed;
}

bool InputHandler::WasKeyReleased(SDL_Scancode key)
{
    int keyCode = SDL_GetKeyFromScancode(key);
    // std::cout << "WasKeyPressed : " << keyCode << " keymapPrev.count(key) : " << keymapPrev.count(keyCode) << " keymap.count(key) : " << keymap.count(keyCode) << std::endl;

    bool wasReleased = (keymapPrev.count(keyCode) != 0) && (keymapPrev[keyCode] == true) && (keymap.count(keyCode) != 0) && (keymap[keyCode] == false);

    keymapPrev[keyCode] = false;

    return wasReleased;
}

void InputHandler::Clean()
{
}
