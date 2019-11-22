#version 420 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

layout (std140, binding = 0) uniform MVP {
    mat4 u_ViewProjection;
    vec3 u_CameraPos;
    float u_Padding;
    mat4 u_Projection;
    mat4 u_StaticView;
};
uniform samplerCube u_CubeMapTexture;

void main() {
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(u_CameraPos - v_Position);
    vec3 R = refract(-I, normalize(-v_Normal), ratio);
    R.y = -R.y;
    R = normalize(R);
    color = vec4(texture(u_CubeMapTexture, R).rgb, 1.0);
    //color = vec4(R.rgb, 1.0);
}
