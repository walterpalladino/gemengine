#include <iostream>

#include "core/events/EventManager.h"
#include "core/input/InputHandler.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"

using namespace std;

EventManager *EventManager::instance = 0;

void EventManager::Init()
{
    //  Register Events
    GEMENGINE_EVENT_TYPE = SDL_RegisterEvents(1);
    cout << "Registered GEMENGINE_EVENT_TYPE as : " << GEMENGINE_EVENT_TYPE << endl;
}

void EventManager::Cleanup()
{
}

EventManagerStatus EventManager::HandleEvents()
{
    EventManagerStatus status = {true, false};

    //  Get first the Custom Events
    SDL_Event event;
    int eventCounter = SDL_PeepEvents(&event, 1,
                                      SDL_GETEVENT,
                                      EventManager::Instance()->GEMENGINE_EVENT_TYPE,
                                      EventManager::Instance()->GEMENGINE_EVENT_TYPE);
    if (eventCounter > 0)
    {
        cout << "GemEngine::PollEvents : Get Custom Event Type : " << event.type << " user code : " << EventManager::GEMEventCodeToString(event.user.code) << endl;

        if (event.user.code == EventManager::GEMEVENT_CODE_PAUSE)
        {
            status.isPaused = true;
        }
        else if (event.user.code == EventManager::GEMEVENT_CODE_RESUME)
        {
            status.isPaused = false;
        }
    }

    //  Get the Standard Events
    bool quit = InputHandler::Instance()->Update();
    if (quit)
    {
        status.isRunning = false;
    }
    /*
    else
    {
        if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_P))
        {
            // cout << "Pause Scene" << endl;
            isPaused = !isPaused;
        }
    }
    */
    else
    {
        //  Resume Scene
        if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_R))
        {
            status.isPaused = false;
        }
    }

    return status;
}
