#version 420 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct PointLight {
    vec3 Color;
    float LinearAttenuation;

    vec3 Position;
    float QuadraticAttenuation;
};

struct DirectionalLight {
    vec3 Color;
    float Strength;

    vec3 Direction;
    float Padding0;
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
    vec3 u_AmbientColor;
    float u_AmbientStrength;

    uint u_PointLightCount;
    uint u_DirectionalLightCount;
    uint u_SpotLightCount;
    float u_Padding0;

    PointLight u_PointLights[70];
    DirectionalLight u_DirectionalLights[10];
    SpotLight u_SpotLights[10];
};

vec3 CalculateDiffuse(vec3 lightCol, vec3 lightDir);
vec3 CalculateSpecular(vec3 lightCol, vec3 lightDir);

float GetAttenuation(float dist, float constant, float linear, float quadratic);

void main() {
    vec4 baseColor = vec4(vec3(0.4f, 0.4f, 0.4f), 1.0f);

    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    // Point Lights
    for (int i = 0; i < u_PointLightCount; ++i) {
        float distanceToLight = length(u_PointLights[i].Position - v_Position);
        float attenuationCutoff = 0.013f;
        float attenuation = GetAttenuation(distanceToLight, 1.0f, u_PointLights[i].LinearAttenuation, u_PointLights[i].QuadraticAttenuation);

        if (attenuation > attenuationCutoff) {
            vec3 lightDir = normalize(u_PointLights[i].Position - v_Position);

            diffuse += attenuation * CalculateDiffuse(u_PointLights[i].Color, lightDir);
            specular += attenuation * CalculateSpecular(u_PointLights[i].Color, lightDir);
        }
    }

    // Directional Lights
    for (int i = 0; i < u_DirectionalLightCount; ++i) {
        diffuse += u_DirectionalLights[i].Strength * CalculateDiffuse(u_DirectionalLights[i].Color, u_DirectionalLights[i].Direction);
        specular += u_DirectionalLights[i].Strength * CalculateSpecular(u_DirectionalLights[i].Color, u_DirectionalLights[i].Direction);
    }

    vec3 ambient = u_AmbientColor * u_AmbientStrength;

    vec3 result = (ambient + diffuse + specular) * baseColor.xyz;
    color = vec4(result, 1.0f);
}


vec3 CalculateDiffuse(vec3 lightCol, vec3 lightDir) {
    vec3 norm = normalize(v_Normal);
    float diff = max(dot(norm, lightDir), 0.0f);
    return lightCol * (diff * u_Material.Diffuse);
}

vec3 CalculateSpecular(vec3 lightCol, vec3 lightDir) {
    vec3 norm = normalize(v_Normal);

    vec3 viewDir = normalize(u_CameraPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.Shininess);
    return lightCol * (spec * u_Material.Specular);
}

float GetAttenuation(float dist, float constant, float linear, float quadratic) {
    float denom = constant + (linear * dist) + (quadratic * dist * dist);
    return 1.0f / denom;
}
