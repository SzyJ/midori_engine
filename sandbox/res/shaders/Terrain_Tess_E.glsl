#version 400 core

layout(quads, cw) in;

in Vertex {
    vec2 c_TexCoord;
    vec3 c_Position;
} IN[];

out Vertex {
    vec2 e_TexCoord;
} OUT;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform float u_TerrainScale;
uniform sampler2D u_DepthMap;

vec4 QuadMixVec4(vec4 a, vec4 b, vec4 c, vec4 d) {
    vec4 p0 = mix(a, c, gl_TessCoord.x);
    vec4 p1 = mix(b, d, gl_TessCoord.x);

    return mix(p0, p1, gl_TessCoord.y);
}

vec3 QuadMixVec3(vec3 a, vec3 b, vec3 c, vec3 d) {
    vec3 p0 = mix(a, c, gl_TessCoord.x);
    vec3 p1 = mix(b, d, gl_TessCoord.x);

    return mix(p0, p1, gl_TessCoord.y);
}

vec2 QuadMixVec2(vec2 a, vec2 b, vec2 c, vec2 d) {
    vec2 p0 = mix(a, c, gl_TessCoord.x);
    vec2 p1 = mix(b, d, gl_TessCoord.x);

    return mix(p0, p1, gl_TessCoord.y);
}

void main(){
    
    vec2 texCoord = QuadMixVec2(
        IN[0].c_TexCoord,
        IN[1].c_TexCoord,
        IN[2].c_TexCoord,
        IN[3].c_TexCoord
    );
    OUT.e_TexCoord = texCoord;

    vec3 worldPos = QuadMixVec3(
        IN[0].c_Position,
        IN[1].c_Position,
        IN[2].c_Position,
        IN[3].c_Position
    );

    worldPos.y += u_TerrainScale * texture(u_DepthMap, texCoord).r;

    gl_Position = u_ViewProjection * u_Transform * vec4(worldPos, 1.0);
}
