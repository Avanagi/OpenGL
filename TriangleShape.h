#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class TriangleShape
{
private:
    ImVec2 triangleStartPosition = ImVec2(0.0f, 0.0f);
    ImVec2 triangleMiddlePosition = ImVec2(0.0f, 0.0f);
    ImVec2 triangleEndPosition = ImVec2(0.0f, 0.0f);
    bool isDrawingTriangle = false;

    struct Triangle {
        ImVec2 startPosition;
        ImVec2 middlePosition;
        ImVec2 endPosition;
        float triangleColor[3] = { 0.0f, 0.0f, 0.0f };
        float lineWidth = 0.1f;
        bool lineStripple = false;
        bool drawFill = false;
        bool dotLine = false;
    };

    std::vector<Triangle> triangles;
    Triangle currentTrian;
    void drawTriangle(const Triangle& rect);

public:
    void render();

    void clearTriangles();
};

