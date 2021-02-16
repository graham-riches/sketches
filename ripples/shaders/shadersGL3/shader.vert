#version 150

uniform mat4 modelViewProjectionMatrix;  //!< default name passed by OF
uniform vec2 u_resolution;
uniform float u_scale;
in vec4 position;
in vec2 texcoord;

// this is how we receive the texture
uniform sampler2DRect tex0;

out vec2 texture_coordinate;

void main()
{    
    vec2 st = gl_Position.xy/u_resolution.xy;    
    vec2 pos = vec2(0.5)-st;
    float r = length(pos)*2.0;
    float a = atan(pos.y,pos.x);

    vec4 modified_position = modelViewProjectionMatrix * position;    
    
    // here we get the red channel value from the texture
    // to use it as vertical displacement
    float displacementY = texture(tex0, texcoord).r * 2;

    // use the displacement we created from the texture data
    // to modify the vertex position
	modified_position.y += displacementY * u_scale;
	
    // this is the resulting vertex position
    gl_Position = modified_position;

    // pass the texture coordinates to the fragment shader
    texture_coordinate = texcoord;
}