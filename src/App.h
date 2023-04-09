#include "core/GemEngine.h"

class App : public GemEngine
{
public:
    App();
    virtual void LoadScenes();
    // Logic loop
    virtual void Loop(float time);
};