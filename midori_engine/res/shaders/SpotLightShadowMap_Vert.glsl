#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_LightViewProjection;

void main(){
    gl_Position = u_LightViewProjection * u_Transform * vec4(a_Position, 1.0);
}
