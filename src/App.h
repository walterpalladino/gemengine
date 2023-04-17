#include "core/GemEngine.h"
#include "core/graphics/console/Console.h"

class App : public GemEngine
{
public:
    App();
    virtual void LoadScenes();
    // Logic loop
    virtual void Loop(float time);
    virtual void Render(float time);
};