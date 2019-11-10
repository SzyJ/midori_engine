#version 400 core

layout(location = 0) out vec4 color;

in Vertex {
    vec2 e_TexCoord;
} IN;

uniform sampler2D u_ColourMap;
uniform sampler2D u_DepthMap;

void main() {
    color = texture(u_ColourMap, IN.e_TexCoord);
}
