#version 120

uniform float fTime;
uniform mat4 mv;

attribute vec3 v;
attribute vec3 n;
attribute vec2 tc;

varying vec3 p;
varying vec3 pn;
varying vec2 uv;

void main(void)
{
    gl_Position = mv * vec4(v, 1.0f);
    gl_Position.z += 0.0f;
    p = gl_Position.xyz;
    vec4 t = mv * vec4(n, 0.0f);
    pn = t.xyz;
    uv = tc;
}
