#include "core/App.h"

class Game : public App
{
public:
    Game();
    virtual void LoadScenes();
    // Logic loop
    virtual void Loop(float time);
};