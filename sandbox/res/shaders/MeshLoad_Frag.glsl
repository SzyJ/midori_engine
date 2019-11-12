#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_TextureCrate;
uniform vec3 u_LightPos;
uniform vec3 u_LightCol;

uniform vec3 u_CameraPos;

void main() {

    vec4 baseColor = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0f);

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_Position);

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightCol;

    // Specular
    vec3 viewDir = normalize(u_CameraPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = 0.5f * spec * u_LightCol;  

    vec3 result = (0.5f + diffuse + specular) * baseColor.xyz;
    color = vec4(result, 1.0);
}
