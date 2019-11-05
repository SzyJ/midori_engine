#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_TextureCrate;

in vec2 v_TexCoord;

void main() {
    color = texture(u_TextureCrate, v_TexCoord);
    //color = vec4(v_TexCoord, 0.0f, 1.0f);
    //color.a = 0.5f;
}
