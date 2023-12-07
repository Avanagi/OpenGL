#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class LineShape
{
private:
    ImVec2 lineStartPosition = ImVec2(0.0f, 0.0f);
    ImVec2 lineEndPosition = ImVec2(0.0f, 0.0f);
    bool isDrawingLine = false;

    struct Line {
        ImVec2 startPosition;
        ImVec2 endPosition;
        float lineColor[3] = { 0.0f, 0.0f, 0.0f };
        float lineWidth = 0.1f;
        bool lineStripple = false;
        bool dotLine = false;
    };

    std::vector<Line> lines;
    Line currentLine;
    void drawLine(const Line& rect);

public:
    void render();

    void clearLines();
};

