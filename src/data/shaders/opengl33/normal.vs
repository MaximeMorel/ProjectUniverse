#version 330 core

uniform mat4 mv;
uniform mat4 mvp;
//uniform mat4 in_matModelViewProj;

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;

out vec3 ex_normal;

void main()
{
    ex_normal = (mv * vec4(in_normal, 0.0)).xyz;
    gl_Position = mvp * vec4(in_vertex, 1.0);
}
