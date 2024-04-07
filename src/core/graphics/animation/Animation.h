#include <string>

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>

#include "core/graphics/textures/TextureManager.h"
#include "math/Point2dInt.h"
#include "core/config/Config.h"

using namespace std;
using json = nlohmann::json;

struct Animation
{
    string name;

    int animationFrames = 0;
    int animationSpeed = 30; //  FPS
    int actualFrame = -1;
    int animationStartTime = 0;

    SDL_Texture *image = NULL;
    int textureWidth = 0;
    int textureHeight = 0;

    Point2dInt offset = Point2dInt(0, 0);
    Point2dInt size = Point2dInt(0, 0);
    /*
        void Load(const char *fileName, int offsetX, int offsetY, int width, int height, int frames, int speed)
        {
            offset.x = offsetX;
            offset.y = offsetY;

            size.x = width;
            size.y = height;

            animationFrames = frames;
            animationSpeed = speed;

            image = TextureManager::Instance()->Add(fileName);
            //  Get texture information
            SDL_QueryTexture(image, NULL, NULL, &textureWidth, &textureHeight);

            actualFrame = 0;
            animationStartTime = -1;
        }
    */
    void Update(float time)
    {
        if (animationStartTime == -1)
        {
            //  First call
            animationStartTime = time;
        }

        //  Calculate the ctual frame based on speed of animation and number of frames
        actualFrame = time - animationStartTime;
        actualFrame *= animationSpeed;
        actualFrame /= 1000;
        actualFrame %= animationFrames;
    }

    void JSONParse(json data)
    {

        name = data.at("name");

        string src = data.at("src");
        string src_file = Config::Instance()->config_data.resource_folder + "/" + src;

        json json_offset = data.at("offset");
        offset = Point2dInt(json_offset.at("x"), json_offset.at("y"));

        json json_size = data.at("size");
        size = Point2dInt(json_size.at("x"), json_size.at("y"));

        animationFrames = data.at("frames");
        animationSpeed = data.at("speed");

        image = TextureManager::Instance()->Add(src_file.c_str());
        //  Get texture information
        SDL_QueryTexture(image, NULL, NULL, &textureWidth, &textureHeight);

        actualFrame = 0;
        animationStartTime = -1;
    }
};
