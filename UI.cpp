#include "UI.h"

using namespace std;

UI::UI(GLFWwindow* window) : window(window) {}

void UI::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    backgroundSettings.render();

    rectangleShape.render();

    triangleShape.render();

    polygonShape.render();

    lineShape.render();

    diskSegment.render();

    if (ImGui::Button("Clear All")) {
        glClearColor(backgroundSettings.getBackgroundColor()[0], backgroundSettings.getBackgroundColor()[1], backgroundSettings.getBackgroundColor()[2], 0);
        triangleShape.clearTriangles();
        lineShape.clearLines();
        rectangleShape.clearRectangles();
        polygonShape.clearPolygons();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

