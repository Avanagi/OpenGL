#include "BackgroundSettings.h"

void BackgroundSettings::render() {
    ImGui::SliderFloat("Scale", &scale, 0.1f, 2.0f);

    ImGui::ColorEdit3("Background Color", backGroundColor);

    if (ImGui::Button("Change Background Color")) {
        glClearColor(backGroundColor[0], backGroundColor[1], backGroundColor[2], 1.0f);
    }

}

float BackgroundSettings::getScale() const {
    return scale;
}

float* BackgroundSettings::getBackgroundColor() const
{
    float* bgColor = new float[3];

    bgColor[0] = backGroundColor[0];
    bgColor[1] = backGroundColor[1];
    bgColor[2] = backGroundColor[2];

    return bgColor;
}
