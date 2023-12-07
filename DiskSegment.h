#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include "BackgroundSettings.h"
#include <glut.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class DiskSegment {
private:
    float lightX = 0.0f;
    float lightY = 0.0f;
    float lightZ = 0.0f;
    bool enableLight = false;
    GLuint customTextureID;
    float diskColor[3] = { 0.0f, 0.0f, 0.0f };
    bool isDrawingDisk = false;
    float rotationAngleX = 0.0f;
    float rotationAngleY = 0.0f;
    float rotationAngleZ = 0.0f;
    bool drawFill = false;
    bool lineStripple = false;
    bool dotLine = false;
    bool drawTexture1 = false;
    bool drawTexture2 = false;
    bool drawWithOwnTexture = false;

public:
    void rotate();

    void render();

    void drawDisk();
};
