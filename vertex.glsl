#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragmentNormal;
out vec3 vPos;

void main()
{
	gl_Position = projection * view * model * vec4(vertexPos, 1);
	vPos = (model * vec4(vertexPos, 1)).xyz;
	fragmentNormal = vertexNormal;
}
