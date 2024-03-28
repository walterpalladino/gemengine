#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

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
    string resource_folder;
    vector<string> scenes;
    //  Console
    int console_x;
    int console_y;
    int console_width;
    int console_height;
    string console_font;
    int console_font_size;
    bool console_enabled;
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
    SDL_FPoint GetWindowScale();
};
