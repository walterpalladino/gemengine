#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "core/gemobject/GemObject.h"
#include "core/scenes/SceneLogic.h"

using namespace std;

struct EventManagerStatus
{
    bool isRunning = false;
    bool isPaused = false;
};

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

    static const Sint32 GEMEVENT_CODE_KEEP_ALIVE = 0,
                        GEMEVENT_CODE_RUN = 1,
                        GEMEVENT_CODE_PAUSE = 2,
                        GEMEVENT_CODE_RESUME = 3,
                        GEMEVENT_CODE_QUIT = 4;

    static string GEMEventCodeToString(Sint32 code)
    {
        if (code == GEMEVENT_CODE_KEEP_ALIVE)
            return "KEEP_ALIVE";
        else if (code == GEMEVENT_CODE_RUN)
            return "RUN";
        else if (code == GEMEVENT_CODE_PAUSE)
            return "PAUSE";
        else if (code == GEMEVENT_CODE_QUIT)
            return "QUIT";
        else
            return "UNKNOWN";
    }

private:
    EventManager() {}
    ~EventManager() {}

    static EventManager *instance;

public:
    Uint32 GEMENGINE_EVENT_TYPE;

public:
    void Init();
    void Cleanup();
    EventManagerStatus HandleEvents();
};