#version 330

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 gWVP;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragVertPos;

void main()
{
	gl_Position = gWVP * vec4(vertPos, 1.0);

	fragTexCoord = texCoord;
	fragNormal = normal;
	fragVertPos = vertPos;

}