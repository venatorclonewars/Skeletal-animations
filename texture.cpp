#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(GLenum textureTarget, const std::string& fileName)
{
	m_textureTarget = textureTarget;
	m_fileName = fileName;
}

bool Texture::load()
{
	stbi_set_flip_vertically_on_load(1);
	int width = 0, height = 0, bpp = 0;
	unsigned char* imageData = stbi_load(m_fileName.c_str(), &width, &height, &bpp, 0);

	if (!imageData)
	{
		printf("Can't load texture '%s'\n", m_fileName.c_str());
	}

	glGenTextures(1, &m_textureObj);
	glBindTexture(m_textureTarget, m_textureObj);
	
	if (m_textureTarget == GL_TEXTURE_2D)
	{
		//glTexImage2D(m_textureTarget, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

		switch (bpp)
		{
		case 1: glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, imageData);
			break;

		case 3: glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			break;
		}
	}

	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(m_textureTarget, 0);

	stbi_image_free(imageData);

	return true;
}

void Texture::bind(GLenum textureUnit) 
{
	glActiveTexture(textureUnit);
	glBindTexture(m_textureTarget, m_textureObj);
}