#version 120

uniform float fTime;

void main(void)
{
    gl_PointSize = 100.0f * (0.5f + 0.5f * sin(fTime));
    //gl_PointSize = 10.0f;
    gl_Position = vec4((0.5f + 0.5f * sin(fTime)) * cos(fTime), (0.5f + 0.5f * cos(fTime)) * sin(fTime), 0.5f, 1.0f);
    //gl_Position = vec4(0.0f, 0.0f, 0.5f, 1.0f);
}
