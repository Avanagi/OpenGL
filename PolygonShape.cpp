#include "PolygonShape.h"

void PolygonShape::render() {
    if (isDrawingPolygon ? ImGui::Button("Stop Drawing Polygon") : ImGui::Button("Draw Polygon")) {
        isDrawingPolygon = !isDrawingPolygon;
        if (!isDrawingPolygon) {
            polygons.push_back(currentPolyg);
            currentPolyg = {};
        }
    }

    if (isDrawingPolygon) {
        ImGui::InputInt("Number of Vertices", &currentPolyg.numVertices);
        if (currentPolyg.numVertices < 3) {
            currentPolyg.numVertices = 3;
        }

        ImGui::InputFloat2("Center Position", (float*)&currentPolyg.centerPosition);
        ImGui::InputFloat("Radius", &currentPolyg.radius);
        ImGui::ColorEdit3("Polygon Color", currentPolyg.polygonColor);
        ImGui::Checkbox("Draw Fill", &currentPolyg.drawFill);
        ImGui::SameLine();
        ImGui::Checkbox("Line Stipple", &currentPolyg.lineStripple);
        ImGui::SameLine();
        ImGui::Checkbox("Dot Line", &currentPolyg.dotLine);
        ImGui::SliderFloat("Line Width", &currentPolyg.lineWidth, 0.1f, 10.0f);
    }

    for (const auto& polyg : polygons) {
        drawPolygon(polyg);
    }
}

void PolygonShape::clearPolygons() {
    polygons.clear();
}

void PolygonShape::drawPolygon(const Polygon& polyg) {
    glLineWidth(polyg.lineWidth);

    if (polyg.drawFill) {
        glBegin(GL_POLYGON);
    }
    else {
        if (polyg.lineStripple) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
        }
        else if (polyg.dotLine) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x0101);
        }
        glBegin(GL_LINE_LOOP);
    }

    glColor3f(polyg.polygonColor[0], polyg.polygonColor[1], polyg.polygonColor[2]);

    for (int i = 0; i < polyg.numVertices; ++i) {
        float angle = 2.0f * 3.14159265358979323846f * i / polyg.numVertices;
        float x = polyg.centerPosition.x + polyg.radius * cos(angle);
        float y = polyg.centerPosition.y + polyg.radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();

    if (polyg.lineStripple || polyg.dotLine) {
        glDisable(GL_LINE_STIPPLE);
    }
}
