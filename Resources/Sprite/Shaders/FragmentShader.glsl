#version 410 core

in vec2 TextureCoords;
out vec4 Color;

uniform sampler2D Sprite;

void main()
{
	Color = vec4(0.0, 0.5, 0.5, 1.0) * texture(Sprite, TextureCoords);	
}