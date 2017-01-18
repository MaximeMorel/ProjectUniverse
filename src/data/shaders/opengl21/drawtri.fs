#version 120

uniform float fTime;
uniform sampler2D tex;

varying vec3 p;
varying vec3 pn;

void main(void)
{
    vec4 lightPos = vec4(10.0f, 10.0f, 0.0f, 1.0f);
    vec3 lDir = normalize(lightPos.xyz - p);
    float v = clamp(dot(lDir, normalize(pn)), 0.0f, 0.75f) + 0.25f;
    gl_FragColor = v * vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
