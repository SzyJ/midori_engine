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

struct PointLight {
    vec3 Color;
    float LinearAttenuation;

    vec3 Position;
    float QuadraticAttenuation;
};

struct DirectionalLight {
    vec3 Color;
    float Padding0;

    vec3 Direction;
    float Padding1;
};

struct SpotLight {
    vec3 Color;
    float InnerCutoff;

    vec3 Position;
    float OuterCutoff;

    vec3 Direction;
    float Padding0;
};

uniform Material u_Material;

uniform sampler2D u_TextureCrate;

layout (std140, binding = 0) uniform MVP {
    mat4 u_ViewProjection;
    vec3 u_CameraPos;
    float u_Padding;
    mat4 u_Projection;
    mat4 u_StaticView;
};

layout (std140, binding = 1) uniform Lights {
    PointLight u_PointLights[];
};

float GetAttenuation(float dist, float constant, float linear, float quadratic);

void main() {
    vec4 baseColor = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0f);

    float distanceToLight = length(u_PointLights[0].Position - v_Position);
    float attenuationCutoff = 0.013f;
    float attenuation = GetAttenuation(distanceToLight, 1.0f, u_PointLights[0].LinearAttenuation, u_PointLights[0].QuadraticAttenuation);
    if (attenuation < attenuationCutoff) {
        color = baseColor;
        return;
    }

    // Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_PointLights[0].Position - v_Position);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = u_PointLights[0].Color * (diff * u_Material.diffuse);

    // Specular
    vec3 viewDir = normalize(u_CameraPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = u_PointLights[0].Color * (spec * u_Material.specular);

    // Attenuation
    diffuse *= attenuation;
    specular *= attenuation;

    // Apply
    vec3 result = (0.5f + diffuse + specular) * baseColor.xyz;
    color = vec4(diffuse, 1.0f);
}

float GetAttenuation(float dist, float constant, float linear, float quadratic) {
    float denom = constant + (linear * dist) + (quadratic * dist * dist);
    return 1.0f / denom;
}