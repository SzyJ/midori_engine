#version 400 core

layout(vertices = 4) out;

in Vertex {
    vec2 v_TexCoord;
    vec3 v_Position;
} IN[];

out Vertex {
    vec2 c_TexCoord;
    vec3 c_Position;
} OUT[];

void main(){
    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = 5.0f;
        gl_TessLevelInner[1] = 5.0f;

        gl_TessLevelOuter[0] = 5.0f;
        gl_TessLevelOuter[1] = 5.0f;
        gl_TessLevelOuter[2] = 5.0f;
        gl_TessLevelOuter[3] = 5.0f;
    }
    
    OUT[gl_InvocationID].c_TexCoord = IN[gl_InvocationID].v_TexCoord;

    OUT[gl_InvocationID].c_Position = IN[gl_InvocationID].v_Position;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
