#version 330 core

#extension GL_ARB_explicit_uniform_location : enable

uniform float fTime;
layout(location = 0) uniform sampler2D tex;

in vec3 p;
in vec3 pn;
in vec2 uv;

out vec4 fragColor;

void main(void)
{
    vec4 lightPos = vec4(10.0f, 10.0f, 0.0f, 1.0f);
    vec3 lDir = normalize(lightPos.xyz - p);
    float v = clamp(dot(lDir, normalize(pn)), 0.0f, 0.75f) + 0.25f;
    fragColor = v * texture(tex, uv);
}
