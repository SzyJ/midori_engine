#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_ColourMap;
uniform sampler2D u_DapthMap;

void main() {
    //color = texture(u_ColourMap, v_TexCoord);
    color = texture(u_DapthMap, v_TexCoord);
    //color = vec4(v_TexCoord, 0.0f, 1.0f);
}
