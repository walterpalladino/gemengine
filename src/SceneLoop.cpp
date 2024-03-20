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
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"

Scene *Scene1Loop(Scene *scene, SDL_Renderer *renderer)
{
    static int sound_channel = 0;

    static Image *ledArrow = (Image *)(scene->Get("led-arrow"));

    static Text *fpsText = (Text *)(scene->Get("text"));

    static Sprite *spriteWalk = (Sprite *)(scene->Get("spriteWalk"));

    //   Scale the image
    Vector3d scale = ledArrow->scale;
    scale.x = 1.0f;
    scale.y = 1.0f;
    ledArrow->scale = scale;

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
    Vector3d rotation = ledArrow->rotation;
    // rotation.z = rotationSpeed * time / 1000.0f;
    rotation.z += rotationSpeed;

    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    ledArrow->rotation = rotation;

    rotation = fpsText->rotation;
    rotation.z += 1;
    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    fpsText->rotation = rotation;
    /*
        char *text = new char[64];
        sprintf(text, "%.2f FPS", GetFPS());
        // sprintf(text, "%04d LFT", GetLastFrameTime());
        // sprintf(text, "%.2f FPS", 1000.0f / GetLastFrameTime());
        fpsText->SetText(text);
        delete[] text;
    */
    // cout << "App::Loop Console operation here..." << endl;
    RenderManager::Instance()->backgroundColor = Point3dInt(216, 216, 216);
    RenderManager::Instance()->backgroundColor = Point3dInt(80, 69, 155);
    Console::Instance()->SetColor(0, 0, 0);
    Console::Instance()->SetColor(136, 126, 203);
    Console::Instance()->SetCursorAt(0, 0);
    Console::Instance()->Print("GemEngine running...");
    Console::Instance()->SetCursorAt(25, 0);
    Console::Instance()->Print("still running...");
    // Console::Instance()->Print(text);

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_1))
    {
        // cout << "Play Music Track" << endl;
        SoundManager::Instance()->PlayTrack("SlingerSwaggerLoop");
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_2))
    {
        // cout << "Stop Music Track" << endl;
        SoundManager::Instance()->StopTrack();
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_3))
    {
        sound_channel = SoundManager::Instance()->PlaySound("ScussesSound1");
        // cout << "Playing Sound : " << sound_channel << endl;
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_4))
    {
        // cout << "Stop Sound : " << sound_channel << endl;
        SoundManager::Instance()->StopSound(sound_channel);
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_7))
    {
        // cout << "Reduce Music Track Volume" << endl;
        int musicVolume = SoundManager::Instance()->SetTrackVolume(-1);
        // cout << "musicVolume = " << musicVolume << endl;
        musicVolume = SoundManager::Instance()->SetTrackVolume(musicVolume - 1);
        // cout << "musicVolume = " << musicVolume << endl;
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_8))
    {
        // cout << "Increase Music Track Volume" << endl;
        int musicVolume = SoundManager::Instance()->SetTrackVolume(-1);
        // cout << "musicVolume = " << musicVolume << endl;
        musicVolume = SoundManager::Instance()->SetTrackVolume(musicVolume + 1);
        // cout << "musicVolume = " << musicVolume << endl;
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_9))
    {
        // cout << "Reduce Master Channels Volume" << endl;
        int masterVolume = SoundManager::Instance()->SetMasterVolume(-1);
        // cout << "masterVolume = " << masterVolume << endl;
        masterVolume = SoundManager::Instance()->SetMasterVolume(masterVolume - 1);
        // cout << "masterVolume = " << masterVolume << endl;
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_0))
    {
        // cout << "Increase Master Channels Volume" << endl;
        int masterVolume = SoundManager::Instance()->SetMasterVolume(-1);
        // cout << "masterVolume = " << masterVolume << endl;
        masterVolume = SoundManager::Instance()->SetMasterVolume(masterVolume + 1);
        // cout << "masterVolume = " << masterVolume << endl;
    }

    //  Sprite Movement
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        spriteWalk->position.x -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        spriteWalk->position.x += 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
    {
        spriteWalk->position.y -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        spriteWalk->position.y += 1;
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_N))
    {
        //  Next Scene
        string newSceneName = "Second Scene";
        cout << "Next Scene : " << newSceneName << endl;
        return SceneManager::Instance()->GetScene(newSceneName);
    }

    return scene;
}