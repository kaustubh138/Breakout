#version 410 core

layout (location = 0) in vec4 Vertex;

out vec2 TextureCoords;

void main()
{
	TextureCoords = Vertex.zw;
	gl_Position = vec4(Vertex.xy, 0.0, 1.0);
}