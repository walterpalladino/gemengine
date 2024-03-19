#include "core/GemEngine.h"
#include "core/graphics/console/Console.h"
#include "core/graphics/text/Text.h"
#include "core/graphics/sprites/Sprite.h"
#include "core/graphics/image/Image.h"

class App : public GemEngine
{
private:
    int sound_channel;
    Image *ledArrow;
    Text *fpsText;
    Sprite *spriteWalk;

public:
    App(string resourceFolder);
    virtual void LoopInit();
    virtual Scene *Loop(float time);
};