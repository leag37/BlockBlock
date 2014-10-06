#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 MVP;

// Output data, will be interpolated for each fragment
out vec2 UV;

void main()
{
	// Output position of the vertex, in clip space
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// UV of the vertex
	vec2 uv = vertexUV;
	uv.y = 1.0 - uv.y;
	UV = uv;
}