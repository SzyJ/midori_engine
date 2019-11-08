#version 400 core

layout(location = 0) out vec4 color;

in Vertex {
    vec2 e_TexCoord;
} IN;

uniform sampler2D u_ColourMap;
uniform sampler2D u_DapthMap;

void main() {
    //color = texture(u_ColourMap, v_TexCoord);
    //color = texture(u_DapthMap, v_TexCoord);
    color = vec4(IN.e_TexCoord, 0.0f, 1.0f);
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
