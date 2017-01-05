#version 130

uniform float fTime;
uniform sampler2D tex;

in vec3 p;
in vec3 pn;

void main(void)
{
    const vec4 lightPos = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 col = lightPos;
    vec3 lDir = normalize(p - lightPos.xyz);
    float v = dot(lDir, normalize(pn));
    gl_FragColor = vec4(1.0f, 0.5f, 0.5f + 0.5f * cos(fTime*2.0f), 1.0f);
    gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
