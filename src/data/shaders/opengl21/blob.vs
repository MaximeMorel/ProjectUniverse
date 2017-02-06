#version 120

//attribute vec3 in_position;

void main()
{
    gl_PointSize = 500.0f;
    //gl_Position = vec4(in_position, 1.0);
    gl_Position = vec4(0.0f, 0.0f, 0.5f, 1.0f);
}
