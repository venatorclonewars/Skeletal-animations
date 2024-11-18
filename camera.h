#pragma once
#include "texture.h"
#include <algorithm>

class Camera
{
public:

    Camera();

    void setPosition(float x, float y, float z);
    void setPosition(Vector3f& pos);

    void onKeyboard(unsigned char key);
    void onMouse(int x, int y);

    Matrix4f getMatrix();

private:

    Vector3f m_forward;
    Vector3f m_up;
    Vector3f m_right;
    
    float m_speed = 2.8f;

public:
    float rotX = 0.0f;
    float rotY = 0.0f;
    Vector3f transformPos;
    Matrix4f cameraTransform;
};