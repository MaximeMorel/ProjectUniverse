#version 120

uniform float fTime;

void main(void)
{
    /*float d = distance(gl_PointCoord, vec2(0.5f, 0.5f));
    if (d > 0.5f || d < 0.35f)
        discard;
        //gl_FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else
        gl_FragColor = vec4(gl_PointCoord, 0.5f + 0.5f * cos(fTime), 1.0f);
    gl_FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);*/
    float d = distance(gl_PointCoord, vec2(0.5f, 1.0f));
    gl_FragColor = vec4(d, 0.0f, 0.5f + 0.5f * cos(fTime*2.0f), 1.0f);
}
