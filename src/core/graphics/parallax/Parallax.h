
#include <SDL2_image/SDL_image.h>

#include "core/gemobject/GemObject.h"
#include "math/Point2dInt.h"

class Parallax : public GemObject
{

private:
    SDL_Texture *image;
    SDL_Rect sourceRect;
    SDL_Rect destRect;
    SDL_Renderer *renderer;

public:
    Parallax(SDL_Renderer *renderer);
    ~Parallax();
    virtual void Init();
    virtual void Update(float time);
    virtual void Cleanup();

    virtual void Render(float time);

    void Load(const char *fileName);

    virtual void JSONParse(json data);

    Point2dInt offset = Point2dInt(0, 0);
};