#version 120

uniform float fTime;
uniform sampler2D tex;

void main(void)
{
    gl_FragColor = vec4(d, 0.0f, 0.5f + 0.5f * cos(fTime*2.0f), 1.0f);
}
