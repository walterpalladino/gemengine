
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

#include "math/Point2dInt.h"

App::App(string resourceFolder) : GemEngine(resourceFolder)
{
}

void App::LoadScenes()
{
    Log::GetInstance()->Info("App::LoadScenes", "Load Scenes");

    string resourceFolder = Config::Instance()->config_data.resource_folder;
    //  TODO : Replace for assets loader
    //  Create Scene
    // Scene *newScene = new Scene(Renderer);
    Scene *newScene = new Scene();
    newScene->Load(StringPrintf("%s/scenes/scene1.json", resourceFolder.c_str()).c_str(), renderer);
    /*
        //  Create Image
        Image *newImage = new Image(renderer);
        newImage->Init();
        //  Load Image
        newImage->Load(StringPrintf("%s/led-arrow.png", resourceFolder.c_str()).c_str());
        newImage->name = string("led-arrow");
        // newImage->scale = Vector3d(1, 1, 1);
        newImage->enabled = true;
        //   Add Image to Scene
        newScene->Add("led-arrow", newImage);

        //  Add text
        Text *newText = new Text(renderer);
        newText->Init("SDL2 text", StringPrintf("%s/fonts/Commodore-64-v6.3.TTF", resourceFolder.c_str()).c_str(), 24);
        newText->position = Vector3d(100, 100, 0);
        newText->scale = Vector3d(1, 1, 1);
        newText->enabled = true;

        //  Add Text to Scene
        newScene->Add("text", newText);

        //  Add Sprites
        Sprite *spriteIdle = new Sprite(renderer);
        //    void Sprite::Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
        spriteIdle->Load(StringPrintf("%s/Gothicvania/ gothicvania patreon collection/Gothic-hero-Files/PNG/gothic-hero-idle.png", resourceFolder.c_str()).c_str(), 0, 0, 38, 48, 4, 4);
        spriteIdle->position = Vector3d(100, 50, 0);
        spriteIdle->scale = Vector3d(1, 1, 1);
        spriteIdle->enabled = true;
        newScene->Add("spriteIdle", spriteIdle);

        Sprite *spriteWalk = new Sprite(renderer);
        //    void Sprite::Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
        spriteWalk->Load(StringPrintf("%s/Gothicvania/ gothicvania patreon collection/Gothic-hero-Files/PNG/gothic-hero-run.png", resourceFolder.c_str()).c_str(), 0, 0, 66, 48, 12, 12);
        spriteWalk->position = Vector3d(200, 100, 0);
        spriteWalk->scale = Vector3d(-1, 1, 1);
        spriteWalk->enabled = true;
        newScene->Add("spriteWalk", spriteWalk);
    */
    newScene->name = string("Start Scene");
    //  Add Scene to Scenes list
    scenes.push_back(newScene);

    activeScene = scenes.front();

    //  Console
    // Console::Instance()->Init(Renderer, 0, 0, 48, 27, "resources/fonts/cga8-thin.png", 8);
    // backgroundColor = Point3dInt(216, 216, 216);

    // Console::Instance()->Init(renderer, 0, 0, 48, 27, "resources/fonts/potash-8x8.png", 8);
    // backgroundColor = Point3dInt(80, 69, 155);
    Log::GetInstance()->Info("App::LoadScenes", "Load Scenes Completed");
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

    if (activeScene->name != string("Start Scene"))
    {
        return;
    }

    //  Scale the image
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
    /*
    Console::Instance()->SetColor(136, 126, 203);
    Console::Instance()->SetCursorAt(0, 0);
    Console::Instance()->Print("GemEngine running...");
    Console::Instance()->SetCursorAt(25, 0);
    Console::Instance()->Print(text);
    */
}

void App::Render(float time)
{
    // if (true)
    //     return;

    GemEngine::Render(time);

    /*
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    Draw::Line(renderer, Point2dInt(10, 10), Point2dInt(50, 50));

    vector<Point2dInt> triangle;
    // triangle.push_back(Point2d(50, 40));
    // triangle.push_back(Point2d(100, 50));
    //     triangle.push_back(Point2d(80, 100));
    triangle.push_back(Point2dInt(50, 50));
    triangle.push_back(Point2dInt(75, 75));
    triangle.push_back(Point2dInt(50, 100));
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    Draw::TriangleFilled(renderer, triangle);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    Draw::PolygonWired(renderer, triangle);

    vector<Point2dInt> square;
    square.push_back(Point2dInt(100, 100));
    square.push_back(Point2dInt(150, 100));
    square.push_back(Point2dInt(150, 150));
    square.push_back(Point2dInt(100, 150));
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    Draw::PolygonFilled(renderer, square);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    Draw::PolygonWired(renderer, square);

    vector<Point2dInt> triangle2;
    triangle2.push_back(Point2dInt(200, 50));
    triangle2.push_back(Point2dInt(201, 100));
    triangle2.push_back(Point2dInt(199, 100));
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    Draw::TriangleFilled(renderer, triangle2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    Draw::PolygonWired(renderer, triangle2);

    // Draw::Line(renderer, Point2d(50, 50), Point2d(100, 50));
    // Draw::Line(renderer, Point2d(100, 50), Point2d(80, 100));
    // Draw::Line(renderer, Point2d(80, 100), Point2d(50, 50));

    vector<Point2dInt> triangleTop;
    triangleTop.push_back(Point2dInt(200, -50));
    triangleTop.push_back(Point2dInt(150, 50));
    triangleTop.push_back(Point2dInt(250, 50));
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    Draw::TriangleFilled(renderer, triangleTop);

    vector<Point2dInt> triangleBottom;
    triangleBottom.push_back(Point2dInt(200, 200));
    triangleBottom.push_back(Point2dInt(150, 250));
    triangleBottom.push_back(Point2dInt(250, 250));
    SDL_SetRenderDrawColor(renderer, 128, 255, 128, 255);
    Draw::TriangleFilled(renderer, triangleBottom);

    //  Check non convex polygon
    vector<Point2dInt> saw;
    saw.push_back(Point2dInt(200, 100));
    saw.push_back(Point2dInt(300, 100));
    saw.push_back(Point2dInt(300, 200));
    saw.push_back(Point2dInt(250, 150));
    saw.push_back(Point2dInt(200, 200));
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    // Draw::PolygonFilled(renderer, saw);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    // Draw::PolygonWired(renderer, saw);

    vector<Point2dInt> star;
    star.push_back(Point2dInt(300, 100));
    star.push_back(Point2dInt(310, 130));
    star.push_back(Point2dInt(340, 140));
    star.push_back(Point2dInt(310, 150));
    star.push_back(Point2dInt(300, 180));
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    Draw::PolygonFilled(renderer, star);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    Draw::PolygonWired(renderer, star);
    */
}
