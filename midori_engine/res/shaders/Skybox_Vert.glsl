#version 420 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

layout (std140) uniform MVP {
    mat4 u_ViewProjection;
    vec3 u_CameraPos;
    float u_Padding;
    mat4 u_Projection;
    mat4 u_StaticView;
};

void main() {
    v_TexCoords = a_Position;
    v_TexCoords.y *= -1.0f;
    vec4 pos = u_Projection * u_StaticView * vec4(a_Position, 1.0);
    gl_Position = pos;
}
