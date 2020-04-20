#pragma once
#ifndef CONFIG_H
#define CONFIG_h

class Config {
  public:
    static bool flightEnabled;

    static const unsigned int SCR_WIDTH = 800;
    static const unsigned int SCR_HEIGHT = 600;

    static bool devMode;

  private:
    Config() {}
};

bool Config::flightEnabled = false;
bool Config::devMode = false;

#endif