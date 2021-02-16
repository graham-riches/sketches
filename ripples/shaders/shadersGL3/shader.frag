#version 150

uniform sampler2DRect tex0;

in vec2 texture_coordinate;

out vec4 output_color;
 
void main()
{
    output_color = texture(tex0, texture_coordinate);
}