#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Config.h"
#include "utils/StringUtils.h"
#include "core/exceptions/ResourceLoadException.h"
#include "utils/Log.h"

using json = nlohmann::json;
using namespace std;

// a simple struct to model a person
struct person
{
    std::string name;
    std::string address;
    int age;
};

Config *Config::instance = 0;

void Config::Load(const string fileName)
{

    try
    {

        string configFileName = config_data.resource_folder + "/" + fileName;

        Log::Instance()->Info("Config::Load", "File: %s", configFileName.c_str());

        json data = json::parse(ifstream(configFileName.c_str()));

        //  Default values
        config_data.window_width = 1280;
        config_data.window_height = 720;
        config_data.virtual_window_width = 384;
        config_data.virtual_window_height = 216;
        config_data.use_virtual_window = true;
        config_data.target_fps = 60;
        config_data.aa_level = 0;

        //  Console
        config_data.console_enabled = false;

        if (data.contains("window"))
        {
            json window_data = data.at("window");
            if (window_data.contains("width"))
            {
                config_data.window_width = window_data.at("width");
            }
            if (window_data.contains("height"))
            {
                config_data.window_height = window_data.at("height");
            }
        }

        if (data.contains("virtual_window"))
        {
            json virtual_window_data = data.at("virtual_window");
            if (virtual_window_data.contains("width"))
            {
                config_data.virtual_window_width = virtual_window_data.at("width");
            }
            if (virtual_window_data.contains("height"))
            {
                config_data.virtual_window_height = virtual_window_data.at("height");
            }
        }

        if (data.contains("render"))
        {
            json render_data = data.at("render");
            if (render_data.contains("use_virtual_window"))
            {
                config_data.use_virtual_window = render_data.at("use_virtual_window");
            }
            if (render_data.contains("target_fps"))
            {
                config_data.target_fps = render_data.at("target_fps");
            }
            if (render_data.contains("aa_level"))
            {
                config_data.aa_level = render_data.at("aa_level");
                config_data.aa_level = clamp(config_data.aa_level, 0, 2);
            }
        }

        if (data.contains("scenes"))
        {
            json scenes_data = data.at("scenes");

            for (auto &[key, val] : scenes_data.items())
            {
                json scene_name = val;
                config_data.scenes.push_back(scene_name.get<string>());
            }
        }

        if (data.contains("console"))
        {
            // cout << "Loading Console Configuration" << endl;
            json console_data = data.at("console");

            config_data.console_x = console_data.at("x");
            config_data.console_y = console_data.at("y");
            config_data.console_width = console_data.at("width");
            config_data.console_height = console_data.at("height");
            config_data.console_font = console_data.at("font");
            config_data.console_font_size = console_data.at("font_size");
            config_data.console_enabled = console_data.at("enabled");
        }
    }
    catch (std::exception &e)
    {
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load configuration file: %s.", fileName.c_str());

        Log::Instance()->Error("Config::Load", buffer);
        throw ResourceLoadException(buffer);
    }
    Log::Instance()->Info("Config::Load", "Config loaded");
}