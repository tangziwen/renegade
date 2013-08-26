#version 110

// we will use two 2D textures
uniform sampler2D tex0;
uniform sampler2D tex1;

void main(void)
{
	// using the interpolated texture coordinate, 
	// find the color of the bottom image
	vec4 color0 = texture2D( tex0, gl_TexCoord[0].st );
	// do the same for the top image
	vec4 color1 = texture2D( tex1, gl_TexCoord[0].st );

	vec4 white=vec4(1.0,1.0,1.0,1.0);
	vec4 result = color0 / (white - color0);
	result = clamp(result, 0.0, 1.0);
	// and set the final pixel color
	gl_FragColor = mix(color0, result, 1.0);
}