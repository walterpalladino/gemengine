
#include <iostream>

#include "App.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"
#include "utils/StringUtils.h"
#include "utils/Log.h"
#include "core/input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/console/Console.h"
#include "core/graphics/draw2d/Draw.h"
#include "core/Config.h"
#include "core/sound/SoundManager.h"

#include "math/Point2dInt.h"

App::App(string resourceFolder) : GemEngine(resourceFolder)
{
}

// Logic loop
void App::Loop(float time)
{

    // cout << "App::Loop"
    //      << " Actual Scene : " << activeScene->name << endl;

    // Log::GetInstance()->Info("App::Loop", "Running the Logic Loop");
    //  if (true)
    //      return;

    if (activeScene == NULL)
    {
        Log::GetInstance()->Info("App::Loop", "activeScene == NULL");
        return;
    }
    /*
        if (activeScene->name != string("Start Scene"))
        {
            return;
        }
        */
    // cout << "activeScene->Get(led-arrow) == NULL = " << (activeScene->Get("led-arrow") == NULL) << endl;
    //   Scale the image
    Vector3d scale = activeScene->Get("led-arrow")->scale;
    scale.x = 1.0f;
    scale.y = 1.0f;
    activeScene->Get("led-arrow")->scale = scale;

    //  Rotate logo image
    float rotationSpeed = 0.0f;

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
    {
        // std::cout << "SDL_SCANCODE_A" << std::endl;
        rotationSpeed = -5.0f;
    }
    else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
    {
        // std::cout << "SDL_SCANCODE_D" << std::endl;
        rotationSpeed = 5.0f;
    }
    // rotationSpeed = 10.0f;
    Vector3d rotation = activeScene->Get("led-arrow")->rotation;
    // rotation.z = rotationSpeed * time / 1000.0f;
    rotation.z += rotationSpeed;

    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->Get("led-arrow")->rotation = rotation;

    rotation = activeScene->Get("text")->rotation;
    rotation.z += 1;
    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->Get("text")->rotation = rotation;

    char *text = new char[64];
    sprintf(text, "%.2f FPS", GetFPS());
    // sprintf(text, "%04d LFT", GetLastFrameTime());
    // sprintf(text, "%.2f FPS", 1000.0f / GetLastFrameTime());
    ((Text *)(activeScene->Get("text")))->SetText(text);
    delete[] text;

    // const char text[] = "GemEngine running...";
    // std::copy(text, text + sizeof(text), consoleBuffer);
    // Console::Instance()->SetColor(0, 0, 0);

    // cout << "App::Loop Console operation here..." << endl;
    backgroundColor = Point3dInt(216, 216, 216);
    backgroundColor = Point3dInt(80, 69, 155);
    Console::Instance()->SetColor(0, 0, 0);
    Console::Instance()->SetColor(136, 126, 203);
    Console::Instance()->SetCursorAt(0, 0);
    Console::Instance()->Print("GemEngine running...");
    Console::Instance()->SetCursorAt(25, 0);
    Console::Instance()->Print("still running...");
    // Console::Instance()->Print(text);

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_1))
    {
        cout << "WasKeyReleased SDL_SCANCODE_1" << endl;
        SoundManager::Instance()->PlayTrack("SlingerSwaggerLoop");
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_2))
    {
        cout << "WasKeyReleased SDL_SCANCODE_2" << endl;
        SoundManager::Instance()->StopTrack("SlingerSwaggerLoop");
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_3))
    {
        cout << "WasKeyReleased SDL_SCANCODE_3" << endl;
        SoundManager::Instance()->PlaySound("ScussesSound1");
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_4))
    {
        cout << "WasKeyReleased SDL_SCANCODE_4" << endl;
        SoundManager::Instance()->StopSound("ScussesSound1");
    }

    // cout << "App::Loop end" << endl;
}
