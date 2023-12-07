#pragma once

#include "imgui.h"
#include "RectangleShape.h"
#include "LineShape.h"
#include "BackgroundSettings.h"
#include "TriangleShape.h"
#include "PolygonShape.h"
#include "DiskSegment.h"

#include <GLFW/glfw3.h>
#include <glut.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UI {
private:
    GLFWwindow* window;
   
    DiskSegment diskSegment;
    PolygonShape polygonShape;
    TriangleShape triangleShape;
    RectangleShape rectangleShape;
    LineShape lineShape;

public:
    BackgroundSettings backgroundSettings;

    UI(GLFWwindow* window);

    void render();
};
