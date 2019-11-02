#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_ColChange;

void main() {
    color = vec4(v_ColChange, 1.0);
}
