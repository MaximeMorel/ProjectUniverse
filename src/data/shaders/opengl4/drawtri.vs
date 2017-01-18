#version 130
#extension GL_ARB_vertex_type_2_10_10_10_rev : enable

uniform float fTime;
uniform mat4 mv;

in vec3 v;
in ivec3 n;

out vec3 p;
out vec3 pn;

void main(void)
{
    gl_Position = mv * vec4(v, 1.0f);
    gl_Position.xyz *= 0.4f;
    gl_Position.z += 0.0f;
    p = gl_Position.xyz;
    vec4 t = mv * vec4(n, 0.0f);
    pn = t.xyz;
}
