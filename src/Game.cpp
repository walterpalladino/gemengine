
#include <iostream>

#include "Game.h"

#include "core/image/Image.h"
#include "core/text/Text.h"
#include "utils/Log.h"
#include "input/InputHandler.h"
#include "core/text/FontsManager.h"

Game::Game() : App()
{
}

void Game::LoadScenes()
{
    Log::GetInstance()->Info("Game::LoadScenes", "Load Scenes");

    //  TODO : Replace for assets loader
    //  Create Scene
    Scene *newScene = new Scene(Renderer);
    //  Craete Image
    Image *newImage = new Image(Renderer);
    newImage->Init();
    //  Load Image
    newImage->Load("resources/logo.png");
    newImage->name = string("resources/logo.png");
    //  Add Image to Scene
    newScene->objects.push_back(newImage);

    //  Add text
    Text *newText = new Text(Renderer);
    newText->Init("SDL2 text", "resources/fonts/Commodore-64-v6.3.TTF", 24);
    newText->position = Vector3d(200, 200, 0);
    newText->scale = Vector3d(2, 2, 1);

    //  Add Text to Scene
    newScene->objects.push_back(newText);

    newScene->name = string("Start Scene");
    //  Add Scene to Scenes list
    scenes.push_back(newScene);

    activeScene = scenes.front();
}

// Logic loop
void Game::Loop(float time)
{
    // Log::GetInstance()->Info("Game::Loop", "Running the Logic Loop");

    //  Scale the image
    Vector3d scale = activeScene->objects[0]->scale;
    scale.x = 0.5f;
    scale.y = 0.5f;
    activeScene->objects[0]->scale = scale;

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
    Vector3d rotation = activeScene->objects[0]->rotation;
    // rotation.z = rotationSpeed * time / 1000.0f;
    rotation.z += rotationSpeed;

    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->objects[0]->rotation = rotation;

    rotation = activeScene->objects[1]->rotation;
    rotation.z += 1;
    if (rotation.z > 360)
        rotation.z = rotation.z - 360;
    if (rotation.z < 0)
        rotation.z = rotation.z + 360;

    activeScene->objects[1]->rotation = rotation;

    char *text = new char[64];
    sprintf(text, "%.2f FPS", GetFPS());
    ((Text *)(activeScene->objects[1]))->SetText(text);
}
