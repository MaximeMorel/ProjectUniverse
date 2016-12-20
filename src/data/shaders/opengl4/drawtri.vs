#version 120

uniform float fTime;

in vec4 v;

void main(void)
{
    gl_Position = v;
}
