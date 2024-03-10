#include "core/GemEngine.h"
#include "core/graphics/console/Console.h"

class App : public GemEngine
{

public:
    App(string resourceFolder);
    virtual void Loop(float time);
    virtual void Render(float time);
};