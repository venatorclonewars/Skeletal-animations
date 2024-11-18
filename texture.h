#pragma once
#include <string>
#include <GL/glew.h>
#include "math.h"

class Texture
{
public:
	Texture(GLenum textureTarget, const std::string& fileName);

    bool load();

    void bind(GLenum textureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    int m_imageBPP = 0;
};

