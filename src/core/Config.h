#pragma once

#include <iostream>

using namespace std;

struct Config_Data
{
    int window_width;
    int window_height;
    int virtual_window_width;
    int virtual_window_height;
    bool use_virtual_window;
    float target_fps;
    int aa_level;
};

class Config
{
public:
    static Config *Instance()
    {
        if (instance == 0)
        {
            instance = new Config();
        }
        return instance;
    }

private:
    Config() {}
    ~Config() {}

    static Config *instance;

public:
    Config_Data config_data;

public:
    void Load(const string fileName);
};
