#version 120

uniform float fTime;

void main(void)
{
    float d = distance(gl_PointCoord, vec2(0.5f, 0.5f));
    if (d > 0.5f || d < 0.35f)
        discard;
        //gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else
        gl_FragColor = vec4(abs(cos(gl_FragCoord.x/1000.0f)), abs(cos(gl_FragCoord.y/1000.0f)), 0.5f + 0.5f * cos(fTime), 1.0f);
    //gl_FragColor = vec4(d, 0.5f, 0.5f, 1.0f);
}
