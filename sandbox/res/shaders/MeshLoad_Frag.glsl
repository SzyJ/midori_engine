#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_TextureCrate;
uniform vec3 u_LightPos;
uniform vec3 u_LightCol;

void main() {
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_Position);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightCol;

    //vec3 result = (0.5f + diffuse) * texture(u_TextureCrate, v_TexCawoord).xyz;
    vec3 result = (0.5f + diffuse) * vec3(1.0f, 1.0f, 1.0f);

    color = vec4(result, 1.0);

    //color = texture(u_TextureCrate, v_TexCoord) * vec4(v_Normal, 1.0f);

    //lightDir += 1;
    //lightDir *= 0.5;
    //color = vec4(lightDir, 1.0f);
}
