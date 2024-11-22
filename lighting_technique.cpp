#include "lighting_technique.h"
#include "material.h"

LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::init()
{
	if (!Technique::init())
		return false;

	if (!addShader(GL_VERTEX_SHADER, "shader.vs"))
		return false;

	if (!addShader(GL_FRAGMENT_SHADER, "shader.fs"))
		return false;

	if (!finalize())
		return false;

	WVPLoc = getUnifromLocation("gWVP");
	samplerLoc = getUnifromLocation("gSampler");
	samplerSpecularExpLoc = getUnifromLocation("gSamplerSpecularExp");

	materialLoc.ambientColor = getUnifromLocation("gMaterial.ambientColor");
	materialLoc.diffuseColor = getUnifromLocation("gMaterial.diffuseColor");
	materialLoc.specularColor = getUnifromLocation("gMaterial.specularColor");

	dirLightLoc.color = getUnifromLocation("gDirectionalLight.color");
	dirLightLoc.ambientIntensity = getUnifromLocation("gDirectionalLight.ambientIntensity");
	dirLightLoc.direction = getUnifromLocation("gDirectionalLight.direction");
	dirLightLoc.diffuseIntensity = getUnifromLocation("gDirectionalLight.diffuseIntensity");

	displayBoneIndex = getUnifromLocation("gDisplayBoneIndex");

	cameraLocalPosLoc = getUnifromLocation("gCameraLocalPos");

	return true;
}

void LightingTechnique::setWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(WVPLoc, 1, GL_TRUE, (const GLfloat*)WVP.mat);
}

void LightingTechnique::setTextureUnit(unsigned int textureUnit)
{
	glUniform1i(samplerLoc, textureUnit);
}

void LightingTechnique::setSpecularExpTextureUnit(unsigned int textureUnit)
{
	glUniform1i(samplerSpecularExpLoc, textureUnit);
}

void LightingTechnique::setDirectionalLight(const DirectionalLight& light)
{
	glUniform3f(dirLightLoc.color, light.color.x, light.color.y, light.color.z);
	glUniform1f(dirLightLoc.ambientIntensity, light.ambientIntensity);

	Vector3f localDirection = light.getLocalDirection();

	glUniform3f(dirLightLoc.direction, localDirection.x, localDirection.y, localDirection.z);
	glUniform1f(dirLightLoc.diffuseIntensity, light.diffuseIntensity);

}

void LightingTechnique::setCameraLocalPos(const Vector3f& cameraLocalPos)
{
	glUniform3f(cameraLocalPosLoc, cameraLocalPos.x, cameraLocalPos.y, cameraLocalPos.z);
}

void LightingTechnique::setMaterial(const Material& material)
{
	glUniform3f(materialLoc.ambientColor, material.ambientColor.x, material.ambientColor.y, material.ambientColor.z);
	glUniform3f(materialLoc.diffuseColor, material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
	glUniform3f(materialLoc.specularColor, material.specularColor.x, material.specularColor.y, material.specularColor.z);
}

void LightingTechnique::setDisplayBoneIndex(int boneIndex)
{
	glUniform1i(displayBoneIndex, boneIndex);

}
