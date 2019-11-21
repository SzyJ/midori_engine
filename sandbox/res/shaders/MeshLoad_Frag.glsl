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
    float DistanceCutoff;
};

uniform Material u_Material;

uniform sampler2D u_Texture;
uniform sampler2D u_DepthMap;
uniform mat4 u_SpotLightViewProjection;

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

float ShadowCalculation(vec3 lightPos);

void main() {
    vec4 baseColor;

    float grayscale = 1.0f;
    baseColor = vec4(grayscale, grayscale, grayscale, 1.0f);

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
            specular += attenuation * CalculateSpecular(u_PointLights[i].Color, -lightDir);
        }
    }

    // Directional Lights
    for (int i = 0; i < u_DirectionalLightCount; ++i) {
        diffuse += u_DirectionalLights[i].Strength * CalculateDiffuse(u_DirectionalLights[i].Color, u_DirectionalLights[i].Direction);
        //specular += u_DirectionalLights[i].Strength * CalculateSpecular(u_DirectionalLights[i].Color, u_DirectionalLights[i].Direction);
    }

    // Spot Lights
    for (int i = 0; i < u_SpotLightCount; ++i) {
        float cutoffDist = u_SpotLights[i].DistanceCutoff;

        float distanceFade = 1.0f - (length(v_Position - u_SpotLights[i].Position) / cutoffDist);
        if (distanceFade < 0.0f) {
            continue;
        }

        vec3 lightDir = normalize(u_SpotLights[i].Position - v_Position);
        float theta = dot(lightDir, normalize(-u_SpotLights[i].Direction));
        float epsilon = u_SpotLights[i].InnerCutoff - u_SpotLights[i].OuterCutoff;
        float intensity = clamp((theta - u_SpotLights[i].OuterCutoff) / epsilon, 0.0f, 1.0f);

        if (theta > u_SpotLights[i].OuterCutoff) {
            vec3 invDir = -u_SpotLights[i].Direction;

            float shadow = ShadowCalculation(u_SpotLights[i].Position);
            diffuse += distanceFade * shadow * intensity * CalculateDiffuse(u_SpotLights[i].Color, invDir);
            specular += distanceFade * shadow * intensity * CalculateSpecular(u_SpotLights[i].Color, invDir);
        }
    }

    vec3 ambient = u_AmbientColor * u_AmbientStrength;

    vec3 result = (ambient + diffuse + specular) * baseColor.xyz;

    float gamma = 2.2f;

    result = pow(result, vec3(gamma));
    color = vec4(result, 1.0f);
}


vec3 CalculateDiffuse(vec3 lightCol, vec3 lightDir) {
    vec3 norm = normalize(v_Normal);
    float diff = max(dot(norm, lightDir), 0.0f);
    return lightCol * (diff * u_Material.Diffuse);
}

vec3 CalculateSpecular(vec3 lightCol, vec3 lightDir) {
    vec3 norm = normalize(-v_Normal);
    vec3 viewDir = normalize(u_CameraPos - v_Position);

    vec3 halfWayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(norm, halfWayDir), 0.0f), u_Material.Shininess);

    return lightCol * (spec *u_Material.Specular);
}

float GetAttenuation(float dist, float constant, float linear, float quadratic) {
    float denom = constant + (linear * dist) + (quadratic * dist * dist);
    return 1.0f / denom;
}

float ShadowCalculation(vec3 lightPos) {
    vec4 fragPosLightSpace = u_SpotLightViewProjection * vec4(v_Position, 1.0);

    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    projCoords = projCoords * 0.5 + 0.5;

    float bias = 0.005f;

    float lightTravelDist = texture(u_DepthMap, projCoords.xy).r + bias;
    float distFromLight = projCoords.z;

    return (lightTravelDist < distFromLight) ? 0.0f : 1.0f;
}
