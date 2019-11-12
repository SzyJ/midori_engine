#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_StaticView;
uniform mat4 u_Projection;
uniform mat4 u_ViewProjection;

void main() {
    v_TexCoords = a_Position;
    v_TexCoords.y *= -1.0f;
    vec4 pos = u_Projection * u_StaticView * vec4(a_Position, 1.0);
    gl_Position = pos;
}
