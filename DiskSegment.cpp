#include "DiskSegment.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb_image.h"
#include <iostream>

GLuint loadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (data) {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return textureID;
    }
    else {
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }
}

void DiskSegment::rotate() {
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f);
}

void DiskSegment::drawDisk() {
    rotate();
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    if (enableLight) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat lightPosition[] = { lightX, lightY, lightZ, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        GLfloat materialAmbient[] = { diskColor[0] * 3.0f, diskColor[1] * 3.0f, diskColor[2] * 3.0f, 1.0f };
        GLfloat materialDiffuse[] = { diskColor[0], diskColor[1], diskColor[2], 1.0f };
        GLfloat materialSpecular[] = { diskColor[0], diskColor[1], diskColor[2], 1.0f };
        GLfloat shininess = 100.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else {
        glColor3f(diskColor[0], diskColor[1], diskColor[2]);
    }

    if (drawFill) {
        if (drawTexture1) {
            glEnable(GL_TEXTURE_2D);
            GLuint yourTextureID = loadTexture("test1.jpg");
            glBindTexture(GL_TEXTURE_2D, yourTextureID);
        }
        else if (drawTexture2) {
            glEnable(GL_TEXTURE_2D);
            GLuint yourTextureID = loadTexture("test2.jpg");
            glBindTexture(GL_TEXTURE_2D, yourTextureID);
        }
        if (drawWithOwnTexture) {
            glGenTextures(1, &customTextureID);
            glBindTexture(GL_TEXTURE_2D, customTextureID);
            int textureWidth = 256;
            int textureHeight = 256;
            unsigned char* customTextureData = new unsigned char[4 * textureWidth * textureHeight];
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, customTextureData);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            delete[] customTextureData;
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, customTextureID);
        }
    }
    else if (lineStripple) {
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPointSize(1.5f);
        rotate();
    }
    else if (dotLine) {
        glPushMatrix();
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x000F);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(3.0f);
        rotate();
    }

    gluPartialDisk(quadric, 0.0f, 0.5f, 100, 1, 0.0f, 180.0f);

    if (drawTexture1 or drawTexture2 or drawWithOwnTexture) {
        glDisable(GL_TEXTURE_2D);
        gluDeleteQuadric(quadric);
    }
    else if (lineStripple) {
        glPointSize(1.0f);
        glDisable(GL_LINE_STIPPLE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_TEXTURE_2D);
        glPopMatrix();
        gluDeleteQuadric(quadric);
    }
    else if (dotLine) {
        glPointSize(1.0f);
        glDisable(GL_POINT_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_TEXTURE_2D);
        glPopMatrix();
        gluDeleteQuadric(quadric);
    }

    if (enableLight) {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
}

void DiskSegment::render() {
    if (isDrawingDisk ? ImGui::Button("Delete Disk") : ImGui::Button("Draw Disk")) {
        isDrawingDisk = !isDrawingDisk;
    }

    if (isDrawingDisk) {
        ImGui::SliderFloat("Rotate X", &rotationAngleX, 0.0f, 180.0f);
        ImGui::SliderFloat("Rotate Y", &rotationAngleY, 0.0f, 180.0f);
        ImGui::SliderFloat("Rotate Z", &rotationAngleZ, 0.0f, 360.0f);
        ImGui::ColorEdit3("Disk Color", diskColor);
        ImGui::Checkbox("Draw Fill", &drawFill);
        ImGui::SameLine();
        ImGui::Checkbox("Line Stripple", &lineStripple);
        ImGui::SameLine();
        ImGui::Checkbox("Dot Line", &dotLine);

        if (drawFill) {
            ImGui::Checkbox("Draw With Texture 1", &drawTexture1);
            ImGui::SameLine();
            ImGui::Checkbox("Draw With Texture 2", &drawTexture2);
            ImGui::Checkbox("Draw With Own Texture", &drawWithOwnTexture);
        }

        ImGui::Text("Light Position");
        ImGui::SliderFloat("Light X", &lightX, -10.0f, 10.0f);
        ImGui::SliderFloat("Light Y", &lightY, -10.0f, 10.0f);
        ImGui::SliderFloat("Light Z", &lightZ, -10.0f, 10.0f);

        if (ImGui::Button("Toggle Light")) {
            enableLight = !enableLight;
        }
    }

    if (isDrawingDisk) { drawDisk(); }
}
