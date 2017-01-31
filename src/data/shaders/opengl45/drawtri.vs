#version 450 core

uniform float fTime;
uniform mat4 mv;
uniform mat4 mvp;

layout(location = 0) in vec3 v;
layout(location = 1) in vec3 n;
layout(location = 2) in vec2 tc;

out vec3 p;
out vec3 pn;
out vec2 uv;

void main(void)
{
    gl_Position = mvp * vec4(v, 1.0f);
    //gl_Position.xyz *= 0.4f;
    gl_Position.z += 0.0f;
    p = gl_Position.xyz;
    pn = (mv * vec4(n, 0.0f)).xyz;
    uv = tc;
}
