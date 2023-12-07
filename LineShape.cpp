#include "LineShape.h"

void LineShape::render() {
    if (isDrawingLine ? ImGui::Button("Stop Drawing Line") : ImGui::Button("Draw Line")) {
        isDrawingLine = !isDrawingLine;
        if (!isDrawingLine) {
            lines.push_back(currentLine);
            currentLine = {};
        }
    }

    if (isDrawingLine) {
        ImGui::InputFloat2("Start Position", (float*)&currentLine.startPosition);
        ImGui::InputFloat2("End Position", (float*)&currentLine.endPosition);
        ImGui::ColorEdit3("Line Color", currentLine.lineColor);
        ImGui::Checkbox("Line Stripple", &currentLine.lineStripple);
        ImGui::SameLine();
        ImGui::Checkbox("Dot Line", &currentLine.dotLine);
        ImGui::SliderFloat("Line Width", &currentLine.lineWidth, 0.1f, 10.0f);
    }

    for (const auto& line : lines) {
        drawLine(line);
    }
}

void LineShape::clearLines()
{
    return lines.clear();
}

void LineShape::drawLine(const Line& line) {
    glLineWidth(line.lineWidth);

    if (line.lineStripple) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF); // шаблон будет применен к каждому пикселю, шаблон означает, что первые восемь пикселей будут отрисованы, а остальные будут пропущены
    }
    else if (line.dotLine) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0101);
    }

    glBegin(GL_LINES);
    glColor3f(line.lineColor[0], line.lineColor[1], line.lineColor[2]);
    glVertex2f(line.startPosition.x, line.startPosition.y);
    glVertex2f(line.endPosition.x, line.endPosition.y);
    glEnd();

    if (line.lineStripple || line.dotLine) {
        glDisable(GL_LINE_STIPPLE);
    }
}