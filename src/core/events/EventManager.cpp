#include "core/events/EventManager.h"

#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/Config.h"

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