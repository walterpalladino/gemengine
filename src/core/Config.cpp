#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Config.h"
#include "../utils/StringUtils.h"
#include "exceptions/ResourceLoadException.h"
#include "../utils/Log.h"

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
        cout << configFileName << endl;
        json data = json::parse(ifstream(configFileName.c_str()));
        // cout << config_data << endl;

        //  Default values
        config_data.window_width = 1280;
        config_data.window_height = 720;
        config_data.virtual_window_width = 384;
        config_data.virtual_window_height = 216;
        config_data.use_virtual_window = true;
        config_data.target_fps = 60;
        config_data.aa_level = 0;

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
    }
    catch (std::exception &e)
    {
        //        cout << e.what() << endl;
        char *buffer = new char[512];
        sprintf(buffer, "Unable to load configuration file: %s.", fileName.c_str());

        Log::GetInstance()->Error("Config::Load", buffer);
        throw ResourceLoadException(buffer);
    }
    Log::GetInstance()->Info("Config::Load", "Config loaded");
}