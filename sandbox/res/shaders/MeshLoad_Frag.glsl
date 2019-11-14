#version 420 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material u_Material;

uniform sampler2D u_TextureCrate;
uniform vec3 u_LightPos;
uniform vec3 u_LightCol;

layout (std140) uniform MVP {
    mat4 u_ViewProjection;
    vec3 u_CameraPos;
    float u_Padding;
    mat4 u_Projection;
    mat4 u_StaticView;
};

//uniform vec3 u_CameraPos;

void main() {
    vec4 baseColor = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0f);

    // Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_Position);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = u_LightCol * (diff * u_Material.diffuse);

    // Specular
    vec3 viewDir = normalize(u_CameraPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = u_LightCol * (spec * u_Material.specular);

    vec3 result = (0.5f + diffuse + specular) * baseColor.xyz;
    color = vec4(result, 1.0);
}
