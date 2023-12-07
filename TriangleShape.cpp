#include "TriangleShape.h"

void TriangleShape::render()
{
    if (isDrawingTriangle ? ImGui::Button("Stop Drawing Triangle") : ImGui::Button("Draw Triangle")) {
        isDrawingTriangle = !isDrawingTriangle;
        if (!isDrawingTriangle) {
            triangles.push_back(currentTrian);
            currentTrian = {};
        }
    }

    if (isDrawingTriangle) {
        ImGui::InputFloat2("Start Position", (float*)&currentTrian.startPosition);
        ImGui::InputFloat2("Middle Position", (float*)&currentTrian.middlePosition);
        ImGui::InputFloat2("End Position", (float*)&currentTrian.endPosition);
        ImGui::ColorEdit3("Rectangle Color", currentTrian.triangleColor);
        ImGui::Checkbox("Draw Fill", &currentTrian.drawFill);
        ImGui::SameLine();
        ImGui::Checkbox("Line Stripple", &currentTrian.lineStripple);
        ImGui::SameLine();
        ImGui::Checkbox("Dot Line", &currentTrian.dotLine);
        ImGui::SliderFloat("Line Width", &currentTrian.lineWidth, 0.1f, 10.0f);
    }

    for (const auto& trian : triangles) {
        drawTriangle(trian);
    }
}

void TriangleShape::clearTriangles()
{
    return triangles.clear();
}

void TriangleShape::drawTriangle(const Triangle& trian)
{
    glLineWidth(trian.lineWidth);

    if (trian.drawFill) {
        glBegin(GL_TRIANGLES);
    }
    else {
        if (trian.lineStripple) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF); // шаблон будет применен к каждому пикселю, шаблон означает, что первые восемь пикселей будут отрисованы, а остальные будут пропущены
        }
        else if (trian.dotLine) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x0101);
        }
        glBegin(GL_LINE_LOOP);
    }

    glColor3f(trian.triangleColor[0], trian.triangleColor[1], trian.triangleColor[2]);
    glVertex2f(trian.startPosition.x, trian.startPosition.y);
    glVertex2f(trian.middlePosition.x, trian.middlePosition.y);
    glVertex2f(trian.endPosition.x, trian.endPosition.y);
    glEnd();

    if (trian.lineStripple || trian.dotLine) {
        glDisable(GL_LINE_STIPPLE);
    }
}
