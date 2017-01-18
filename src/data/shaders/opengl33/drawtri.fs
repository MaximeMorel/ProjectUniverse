#version 330 core

uniform float fTime;
uniform sampler2D tex;

in vec3 p;
in vec3 pn;

out vec4 col;

void main(void)
{
    vec4 lightPos = vec4(10.0f, 10.0f, 0.0f, 1.0f);
    vec3 lDir = normalize(lightPos.xyz - p);
    float v = clamp(dot(lDir, normalize(pn)), 0.0f, 0.75f) + 0.25f;
    //gl_FragColor = vec4(1.0f, 0.5f, 0.5f + 0.5f * cos(fTime*2.0f), 1.0f);
    //gl_FragColor = v * vec4(1.0f, 0.0f, 0.0f, 1.0f);
    col = v * vec4(1.0f, 0.0f, 0.0f, 1.0f);
}