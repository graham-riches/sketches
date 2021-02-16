#version 150

uniform mat4 modelViewProjectionMatrix;  //!< default name passed by OF
uniform float scale;
in vec4 position;
in vec2 texcoord;

// this is how we receive the texture
uniform sampler2DRect tex0;

out vec2 texture_coordinate;

void main()
{    
    vec4 modified_position = modelViewProjectionMatrix * position;    
    
    // here we get the red channel value from the texture
    // to use it as vertical displacement
    float displacementY = texture(tex0, texcoord).r;

    // use the displacement we created from the texture data
    // to modify the vertex position
	modified_position.y += displacementY * scale;
	
    // this is the resulting vertex position
    gl_Position = modified_position;

    // pass the texture coordinates to the fragment shader
    texture_coordinate = texcoord;
}