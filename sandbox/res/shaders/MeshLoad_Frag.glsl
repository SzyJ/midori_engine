#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_TextureCrate;

void main() {
    color = texture(u_TextureCrate, v_TexCoord) * vec4(v_Normal, 1.0f);
    //color = vec4(v_Normal, 1.0f);
}
