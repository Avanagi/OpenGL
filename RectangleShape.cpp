#include "RectangleShape.h"

void RectangleShape::render() {
    if (isDrawingRectangle ? ImGui::Button("Stop Drawing Rectangle") : ImGui::Button("Draw Rectangle")) {
        isDrawingRectangle = !isDrawingRectangle;
        if (!isDrawingRectangle) {
            rectangles.push_back(currentRect);
            currentRect = {};
        }
    }

    if (isDrawingRectangle) {
        ImGui::InputFloat2("Start Position", (float*)&currentRect.startPosition);
        ImGui::InputFloat2("End Position", (float*)&currentRect.endPosition);
        ImGui::ColorEdit3("Rectangle Color", currentRect.rectangleColor);
        ImGui::Checkbox("Draw Fill", &currentRect.drawFill);
        ImGui::SameLine();
        ImGui::Checkbox("Line Stripple", &currentRect.lineStripple);
        ImGui::SameLine();
        ImGui::Checkbox("Dot Line", &currentRect.dotLine);
        ImGui::SliderFloat("Line Width", &currentRect.lineWidth, 0.1f, 10.0f);
    }

    for (const auto& rect : rectangles) {
        drawRectangle(rect);
    }
}

void RectangleShape::clearRectangles()
{
    return rectangles.clear();
}

void RectangleShape::drawRectangle(const Rectangle& rect) {
    glLineWidth(rect.lineWidth);

    if (rect.drawFill) {
        glBegin(GL_QUADS);
    }
    else {
        if (rect.lineStripple) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF); // шаблон будет применен к каждому пикселю, шаблон означает, что первые восемь пикселей будут отрисованы, а остальные будут пропущены
        }
        else if (rect.dotLine) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x0101);
        }
        glBegin(GL_LINE_LOOP);
    }

    glColor3f(rect.rectangleColor[0], rect.rectangleColor[1], rect.rectangleColor[2]);
    glVertex2f(rect.startPosition.x, rect.startPosition.y);
    glVertex2f(rect.endPosition.x, rect.startPosition.y);
    glVertex2f(rect.endPosition.x, rect.endPosition.y);
    glVertex2f(rect.startPosition.x, rect.endPosition.y);
    glEnd();

    if (rect.lineStripple || rect.dotLine) {
        glDisable(GL_LINE_STIPPLE);
    }
}