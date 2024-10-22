#version 330 core
out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_InputTexture;

void main() {
    vec3 col = texture(u_InputTexture, v_TexCoords).rgb;
    color = vec4(col, 1.0f);
}
