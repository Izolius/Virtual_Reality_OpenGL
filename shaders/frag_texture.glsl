#version 330 core
out vec4 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 objectColor;

void main()
{
	color = texture(ourTexture, TexCoord);
}
