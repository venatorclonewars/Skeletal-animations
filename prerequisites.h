#pragma once
#include <cstdlib>
#include "math.h"

struct Vertex
{
public:
    Vector3f pos;
    Vector3f color;

public:
    Vertex() {}

    Vertex(float x, float y)
    {
        pos = Vector3f(x, y, 0.0f);

        float red = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue = (float)rand() / (float)RAND_MAX;
        color = Vector3f(red, green, blue);
    }

};