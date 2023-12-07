#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class RectangleShape
{
private:
    ImVec2 rectStartPosition = ImVec2(0.0f, 0.0f);
    ImVec2 rectEndPosition = ImVec2(0.0f, 0.0f);
    bool isDrawingRectangle = false;

    struct Rectangle {
        ImVec2 startPosition;
        ImVec2 endPosition;
        float rectangleColor[3] = { 0.0f, 0.0f, 0.0f };
        float lineWidth = 0.1f;
        bool lineStripple = false;
        bool drawFill = false;
        bool dotLine = false;
    };

    std::vector<Rectangle> rectangles;
    Rectangle currentRect;
    void drawRectangle(const Rectangle& rect);

public:
    void render();

    void clearRectangles();
};

