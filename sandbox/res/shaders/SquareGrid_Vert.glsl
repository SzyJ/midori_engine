#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec3 v_ColChange;

void main() {
    v_ColChange = vec3(u_Transform[3][0], u_Transform[3][1], u_Transform[3][2]);
    v_Position = a_Position;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
