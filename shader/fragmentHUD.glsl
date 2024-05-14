#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texHud;

void main()
{
	vec4 texColor = texture(texHud, TexCoord);
	if (texColor.a < 0.3) discard;
	FragColor = texColor;
	//FragColor = vec4(1.0,1.0,1.0,1.0);
}
