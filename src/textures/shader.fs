#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TextCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float opacity;

void main()
{
	float scaleFactor = 1.0f;
	vec2 TextCoordMagnified = vec2(TextCoord.s * scaleFactor - scaleFactor / 2, TextCoord.t * scaleFactor - scaleFactor / 2);
	vec2 TextCoordReversed = vec2(abs(TextCoord.s - 1.0f) * 1.0f, TextCoord.t * 1.0f);
	FragColor = mix(texture(texture1, TextCoordMagnified), texture(texture2, TextCoordReversed), opacity);
}
