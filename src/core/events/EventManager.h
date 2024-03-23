#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

using namespace std;

class EventManager
{

public:
    static EventManager *Instance()
    {
        if (instance == 0)
        {
            instance = new EventManager();
        }
        return instance;
    }

private:
    EventManager() {}
    ~EventManager() {}

    static EventManager *instance;

public:
    Uint32 GEMENGINE_EVENT_TYPE;
    Sint32 GEMENGINE_EVENT_CODE = 1;

public:
    void Init();
    void Cleanup();
};