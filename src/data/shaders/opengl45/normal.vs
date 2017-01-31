#version 450 core

layout(location = 0) uniform mat4 mv;
layout(location = 1) uniform mat4 mvp;
//layout(location = 1) uniform mat4 in_matModelViewProj;

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_texcoords;

out vec3 ex_normal;

void main()
{
    ex_normal = (mv * vec4(in_normal, 0.0f)).xyz;
    gl_Position = mvp * vec4(in_vertex, 1.0f);
}
