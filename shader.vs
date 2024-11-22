#version 330

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in ivec4 boneIDs;
layout (location = 4) in vec4 weights;

uniform mat4 gWVP;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragVertPos;
flat out ivec4 fragBoneIDs;
out vec4 fragWeights;

void main()
{
	gl_Position = gWVP * vec4(vertPos, 1.0);

	fragTexCoord = texCoord;
	fragNormal = normal;
	fragVertPos = vertPos;

	fragBoneIDs = boneIDs;
	fragWeights = weights;

}