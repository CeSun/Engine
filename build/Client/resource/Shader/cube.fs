#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
    float ambientStrength = 0.1;                    // 环境光强度
    vec3 ambient = ambientStrength * vec3(1.0,1.0,1.0);
	FragColor = vec4(ambient, 1.0) * texture(texture1, TexCoord);
}