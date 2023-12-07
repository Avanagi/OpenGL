#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>

class BackgroundSettings
{
private:
    float scale = 1.0f;
    float backGroundColor[3] = { 0.0f, 0.0f, 0.0f };

public:

    void render();

    float getScale() const;

    float *getBackgroundColor() const;
};

