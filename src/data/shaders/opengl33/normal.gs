#version 330 core

layout(triangles) in;
layout(line_strip) out;
layout(max_vertices = 6) out;

in vec3 ex_normal[];

void main()
{
    for(int i = 0; i < gl_in.length(); ++i)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = gl_in[i].gl_Position + vec4(ex_normal[i], 0.0);
        EmitVertex();
        EndPrimitive();
    }
}
