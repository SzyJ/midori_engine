#version 420 core

out vec4 FragColor;

in vec3 v_TexCoords;

uniform samplerCube u_CubeMapTexture;

void main() {
    FragColor = texture(u_CubeMapTexture, v_TexCoords);
}
