#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class PolygonShape
{
private:
    bool isDrawingPolygon = false;

    struct Polygon {
        float polygonColor[3] = { 0.0f, 0.0f, 0.0f };
        float lineWidth = 0.1f;
        bool lineStripple = false;
        bool drawFill = false;
        bool dotLine = false;
        int numVertices = 3;
        ImVec2 centerPosition;
        float radius = 1.0f;
    };

    std::vector<Polygon> polygons;
    Polygon currentPolyg;
    void drawPolygon(const Polygon& polyg);

public:
    void render();
    void clearPolygons();
};

