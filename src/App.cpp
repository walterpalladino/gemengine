
#include <iostream>

#include "App.h"

#include "core/graphics/image/Image.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/text/Text.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/graphics/text/FontsManager.h"
#include "core/graphics/console/Console.h"
#include "core/graphics/Draw.h"

#include "math/Point2d.h"

App::App() : GemEngine()
{
}

void App::LoadScenes()
{
    Log::GetInstance()->Info("App::LoadScenes", "Load Scenes");

    //  TODO : Replace for assets loader
    //  Create Scene
    // Scene *newScene = new Scene(Renderer);
    Scene *newScene = new Scene();

    //  Create Image
    Image *newImage = new Image(Renderer);
    newImage->Init();
    //  Load Image
    newImage->Load("resources/logo.png");
    newImage->name = string("resources/logo.png");
    // newImage->scale = Vector3d(1, 1, 1);
    newImage->enabled = true;
    //   Add Image to Scene
    newScene->Add("logo", newImage);

    //  Add text
    Text *newText = new Text(Renderer);
    newText->Init("SDL2 text", "resources/fonts/Commodore-64-v6.3.TTF", 24);
    newText->position = Vector3d(100, 100, 0);
    newText->scale = Vector3d(1, 1, 1);
    newText->enabled = true;

    //  Add Text to Scene
    newScene->Add("text", newText);

    //  Add Sprites
    Sprite *spriteIdle = new Sprite(Renderer);
    //    void Sprite::Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
    spriteIdle->Load("resources/Gothicvania/ gothicvania patreon collection/Gothic-hero-Files/PNG/gothic-hero-idle.png", 0, 0, 38, 48, 4, 4);
    spriteIdle->position = Vector3d(100, 50, 0);
    spriteIdle->scale = Vector3d(1, 1, 1);
    spriteIdle->enabled = true;
    newScene->Add("spriteIdle", spriteIdle);

    Sprite *spriteWalk = new Sprite(Renderer);
    //    void Sprite::Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
    spriteWalk->Load("resources/Gothicvania/ gothicvania patreon collection/Gothic-hero-Files/PNG/gothic-hero-run.png", 0, 0, 66, 48, 12, 12);
    spriteWalk->position = Vector3d(200, 100, 0);
    spriteWalk->scale = Vector3d(-1, 1, 1);
    spriteWalk->enabled = true;
    newScene->Add("spriteWalk", spriteWalk);

    newScene->name = string("Start Scene");
    //  Add Scene to Scenes list
    scenes.push_back(newScene);

    activeScene = scenes.front();

    //  Console
    // Console::Instance()->Init(Renderer, 0, 0, 48, 27, "resources/fonts/cga8-thin.png", 8);
    // backgroundColor = Point3dInt(216, 216, 216);

    Console::Instance()->Init(Renderer, 0, 0, 48, 27, "resources/fonts/potash-8x8.png", 8);
    backgroundColor = Point3dInt(80, 69, 155);
}

// Logic loop
void App::Loop(float time)
{

    // Log::GetInstance()->Info("App::Loop", "Running the Logic Loop");

    //  Scale the image
    Vector3d scale = activeScene->Get("logo")->scale;
    scale.x = 0.25f;
    scale.y = 0.25f;
    activeScene->Get("logo")->scale = scale;

    //  Rotate logo image
    float rotationSpeed = 0.0f;

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
    {
        // std::cout << "SDL_SCANCODE_A" << std::endl;
        rotationSpeed = -10.0f;
    }
    else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
    {
        // std::cout << "SDL_SCANCODE_D" << std::endl;
        rotationSpeed = 10.0f;
    }
    // rotationSpeed = 10.0f;
    Vector3d rotation = activeScene->Get("logo")->rotation;
    // rotation.z = rotationSpeed * time / 1000.0f;
    rotation.z += rotationSpeed;

    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->Get("logo")->rotation = rotation;

    rotation = activeScene->Get("text")->rotation;
    rotation.z += 1;
    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->Get("text")->rotation = rotation;

    char *text = new char[64];
    sprintf(text, "%.2f FPS", GetFPS());
    ((Text *)(activeScene->Get("text")))->SetText(text);

    // const char text[] = "GemEngine running...";
    // std::copy(text, text + sizeof(text), consoleBuffer);
    // Console::Instance()->SetColor(0, 0, 0);
    Console::Instance()->SetColor(136, 126, 203);
    Console::Instance()->SetCursorAt(0, 0);
    Console::Instance()->Print("GemEngine running...");
    Console::Instance()->SetCursorAt(25, 0);
    Console::Instance()->Print(text);
}

void App::Render(float time)
{
    GemEngine::Render(time);
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    Draw::Line(Renderer, Point2d(10, 10), Point2d(50, 50));
}
