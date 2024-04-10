#include <iostream>

#include "app/Scene1.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"
#include "utils/StringUtils.h"
#include "utils/Log.h"
#include "core/input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/console/Console.h"
#include "core/graphics/draw2d/Draw.h"
#include "core/sound/SoundManager.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"
#include "core/renderer/RenderManager.h"
#include "core/Context.h"
#include "core/GemEngine.h"
#include "core/events/EventManager.h"

using namespace std;

void Scene1::Init(Scene *scene)
{

    this->scene = scene;

    ledArrow = scene->GetByName("led-arrow");

    knight = scene->GetByName("knight");
    knightSprite = (Sprite *)(knight->GetComponentsByType(ComponentType::Sprite)[0]);
    knightCollider = (Collider *)(knight->GetComponentsByType(ComponentType::Collider)[0]);
    knightCollider->SetRenderCollider(true);
    knightCollider->SetRenderCollisions(true);

    text = scene->GetByName("text");
    fpsText = (Text *)(text->GetComponentsByType(ComponentType::Text)[0]);

    string console_text =
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "    HAAAAAAAAAAAAJ                              "
        "   AAA   AAAAAAAAAAAAA                          "
        " AA  AAAAAAAAAAAAAAAAAAAAAAQ     A A            "
        "      AAAAAAAAAAAAAAA     BAAAA AAAAAAAAA       "
        "    AAA     A  JA             AAA  A    A       "
        "   A                          B  D AA  AU       "
        "                            A A  W AA A OA      "
        "                            A UWW        A      "
        "                              AAAA AAAAAAW      "
        "                          W     AAAA    A       "
        "                        AAAAAAAAAAAAAAAAAAAA    "
        "                 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                "
        "                                                ";
    Console::Instance()->SetBuffer(console_text.c_str());

    GemObject *audio_tracks = scene->GetByName("audio_tracks");
    sound = (Sound *)(audio_tracks->GetComponentsByType(ComponentType::Sound)[0]);
    track = (Track *)(audio_tracks->GetComponentsByType(ComponentType::Track)[0]);
}

SceneTransition Scene1::Loop(float time)
{

    SceneTransition sceneTransition;
    // cout << "Scene1::Loop" << endl;

    //   Scale the image
    Vector3d scale = ledArrow->transform.scale;
    scale.x = 1.0f;
    scale.y = 1.0f;
    ledArrow->transform.scale = scale;

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
    Vector3d rotation = ledArrow->transform.rotation;
    // rotation.z = rotationSpeed * time / 1000.0f;
    rotation.z += rotationSpeed;

    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    ledArrow->transform.rotation = rotation;

    rotation = text->transform.rotation;
    rotation.z += 1;
    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    text->transform.rotation = rotation;

    char *text_info = new char[64];
    sprintf(text_info, "%.2f FPS", Context::Instance()->GetFPS());
    // sprintf(text, "%04d LFT", GetLastFrameTime());
    // sprintf(text, "%.2f FPS", 1000.0f / GetLastFrameTime());
    fpsText->SetText(text_info);
    delete[] text_info;

    // cout << "App::Loop Console operation here..." << endl;
    RenderManager::Instance()->backgroundColor = Point3dInt(216, 216, 216);
    RenderManager::Instance()->backgroundColor = Point3dInt(80, 69, 155);
    Console::Instance()->SetColor(0, 0, 0);
    Console::Instance()->SetColor(136, 126, 203);

    //    Console::Instance()->SetCursorAt(0, 0);
    //    Console::Instance()->Print("GemEngine running...");
    //    Console::Instance()->SetCursorAt(25, 0);
    //    Console::Instance()->Print("still running...");
    // Console::Instance()->Print(text);

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_1))
    {
        // cout << "Play Music Track" << endl;
        // SoundManager::Instance()->PlayTrack("SlingerSwaggerLoop");
        track->Play();
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_2))
    {
        // cout << "Stop Music Track" << endl;
        // SoundManager::Instance()->StopTrack();
        track->Stop();
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_3))
    {
        // sound_channel = SoundManager::Instance()->PlaySound("ScussesSound1");
        //  cout << "Playing Sound : " << sound_channel << endl;
        sound->Play();
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_4))
    {
        // cout << "Stop Sound : " << sound_channel << endl;
        // SoundManager::Instance()->StopSound(sound_channel);
        sound->Stop();
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_7))
    {
        // cout << "Reduce Music Track Volume" << endl;
        // int musicVolume = SoundManager::Instance()->SetTrackVolume(-1);
        int musicVolume = track->SetVolume(-1);
        // cout << "musicVolume = " << musicVolume << endl;
        // musicVolume = SoundManager::Instance()->SetTrackVolume(musicVolume - 1);
        musicVolume = track->SetVolume(musicVolume - 1);
        // cout << "musicVolume = " << musicVolume << endl;
    }
    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_8))
    {
        // cout << "Increase Music Track Volume" << endl;
        // int musicVolume = SoundManager::Instance()->SetTrackVolume(-1);
        int musicVolume = track->SetVolume(-1);
        // cout << "musicVolume = " << musicVolume << endl;
        // musicVolume = SoundManager::Instance()->SetTrackVolume(musicVolume + 1);
        musicVolume = track->SetVolume(musicVolume + 1);
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

    //  Sprite Animations
    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_Z))
    {
        int actualAnimation = knightSprite->GetActualAnimation() - 1;
        if (actualAnimation < 0)
        {
            actualAnimation = knightSprite->GetAnimationsCount() - 1;
        }
        knightSprite->SetActualAnimation(actualAnimation);
    }
    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_X))
    {
        int actualAnimation = knightSprite->GetActualAnimation() + 1;
        if (actualAnimation == knightSprite->GetAnimationsCount())
        {
            actualAnimation = 0;
        }
        knightSprite->SetActualAnimation(actualAnimation);
    }

    //  Sprite Movement
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        knight->transform.position.x -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        knight->transform.position.x += 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
    {
        knight->transform.position.y -= 1;
    }
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        knight->transform.position.y += 1;
    }

    if (InputHandler::Instance()->WasKeyReleased(SDL_SCANCODE_N))
    {
        //  Next Scene
        string newSceneName = "Second Scene";
        // cout << "Next Scene : " << newSceneName << endl;
        sceneTransition.scene = SceneManager::Instance()->GetScene(newSceneName);
        return sceneTransition;
    }

    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_P))
    {
        cout << "Pause Scene" << endl;
        // sceneTransition.isPaused = true;
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); // or SDL_zero(event)
        event.type = EventManager::Instance()->GEMENGINE_EVENT_TYPE;
        event.user.code = EventManager::GEMEVENT_CODE_PAUSE;
        event.user.data1 = 0;
        event.user.data2 = 0;

        int status = SDL_PushEvent(&event);
    }

    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_O))
    {
        cout << "Fire Custom Event" << endl;

        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); // or SDL_zero(event)
        event.type = EventManager::Instance()->GEMENGINE_EVENT_TYPE;
        event.user.code = EventManager::GEMEVENT_CODE_KEEP_ALIVE;
        event.user.data1 = 0;
        event.user.data2 = 0;

        int status = SDL_PushEvent(&event);
        cout << "SDL_PushEvent status : " << status << endl;
    }

    //  Console Scroll
    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_I))
    {
        Console::Instance()->Shift(CONSOLE_SHIFT_UP, true);
    }
    else if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_K))
    {
        Console::Instance()->Shift(CONSOLE_SHIFT_DOWN, true);
    }
    if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_J))
    {
        Console::Instance()->Shift(CONSOLE_SHIFT_LEFT, true);
    }
    else if (InputHandler::Instance()->WasKeyPressed(SDL_SCANCODE_L))
    {
        Console::Instance()->Shift(CONSOLE_SHIFT_RIGHT, true);
    }

    sceneTransition.scene = scene;
    return sceneTransition;
}

void Scene1::Clean()
{
    // cout << "Scene1::Clean" << endl;
}

void Scene1::OnMouseButtonDown(GemObject *object, SDL_Event *event)
{
    cout << "Scene1::OnMouseButtonDown" << endl;
    cout << "object->name : " << object->name << endl;
    cout << "event->type : " << event->type << endl;
    // cout << "event->button.button : " << event->button.button << endl;

    if (event->button.button == SDL_BUTTON_LEFT)
    {
        cout << "Left Mouse Button Pressed." << endl;
    }
    else if (event->button.button == SDL_BUTTON_MIDDLE)
    {
        cout << "Middle Mouse Button Pressed." << endl;
    }
    else if (event->button.button == SDL_BUTTON_RIGHT)
    {
        cout << "Right Mouse Button Pressed." << endl;
    }
}

void Scene1::OnMouseButtonUp(GemObject *object, SDL_Event *event)
{
    cout << "Scene1::OnMouseButtonUp" << endl;
    cout << "object->name : " << object->name << endl;
    cout << "event->type : " << event->type << endl;
    // cout << "event->button.button : " << event->button.button << endl;

    if (event->button.button == SDL_BUTTON_LEFT)
    {
        cout << "Left Mouse Button Pressed." << endl;
    }
    else if (event->button.button == SDL_BUTTON_MIDDLE)
    {
        cout << "Middle Mouse Button Pressed." << endl;
    }
    else if (event->button.button == SDL_BUTTON_RIGHT)
    {
        cout << "Right Mouse Button Pressed." << endl;
    }
}

void Scene1::OnMouseMove(GemObject *object, SDL_Event *event)
{
    cout << "Scene1::OnMouseMove" << endl;
    cout << "object->name : " << object->name << endl;
    cout << "event->type : " << event->type << endl;
}
