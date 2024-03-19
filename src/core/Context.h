#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core/gemobject/GemObject.h"

using namespace std;

class Context
{
public:
    static Context *Instance()
    {
        if (instance == 0)
        {
            instance = new Context();
        }
        return instance;
    }

private:
    Context() {}
    ~Context() {}

    static Context *instance;

public:
    unordered_map<string, GemObject *> objects;
};