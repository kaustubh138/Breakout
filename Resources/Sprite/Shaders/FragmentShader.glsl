#version 330 core
in vec2 texture_coords;
out vec4 color;

uniform sampler2D sprite;
uniform vec3 sprite_color;

void main()
{
    color = vec4(sprite_color, 1.0) * texture(sprite, texture_coords);
}