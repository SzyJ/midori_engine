#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_TextureCrate;

in vec2 v_TexCoord;

void main() {
    color = texture(u_TextureCrate, v_TexCoord);
}
