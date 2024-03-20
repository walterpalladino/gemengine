#include "core/Context.h"

Context *Context::instance = 0;

void Context::InitFPSCounter()
{
    firstRenderTick = SDL_GetTicks();
    lastRenderTime = 0;

    totalFrames = 0;

    targetFrameTime = (1000 / targetFPS);
}

float Context::GetFPS()
{
    float elapsedTimeFromStart = endFrameTick - firstRenderTick;
    return elapsedTimeFromStart > 0 ? (float)totalFrames / elapsedTimeFromStart * 1000.0f : 0.0;
}

float Context::StartFPSFrameCounter()
{
    startFrameTick = SDL_GetTicks();
    return startFrameTick - firstRenderTick;
}

void Context::WaitForEndFrame()
{
    lastRenderTime = SDL_GetTicks() - startFrameTick;

    if (lastRenderTime >= targetFrameTime)
        SDL_Delay(1); // Breath
    else
        SDL_Delay(targetFrameTime - lastRenderTime); // Breath

    totalFrames = totalFrames + 1;

    endFrameTick = SDL_GetTicks();

    lastFrameTime = endFrameTick - startFrameTick;
}