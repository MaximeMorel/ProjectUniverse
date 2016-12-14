#version 120

uniform float fTime;
uniform sampler2D tex;

vec4 rainbow(vec2 p, vec2 center)
{
    vec3 res;
    float f = distance(p, center) * 2.0f;
    /*convert to long rainbow RGB*/
    float a = (1.0f - f) / 0.2f;
    int X = int(floor(a));
    int Y = int(floor(255.0f*(a-X)));
    if (X==0)
        res = vec3(255.0f, Y, 0.0f);
    else if (X==1)
        res = vec3(255.0f - Y, 255.0f, 0.0f);
    else if (X==2)
        res = vec3(0.0f, 255.0f, Y);
    else if (X==3)
        res = vec3(0.0f, 255.0f - Y, 255.0f);
    else if (X==4)
        res = vec3(Y, 0.0f, 255.0f);
    else if (X==5)
        res = vec3(255.0f, 0.0f, 255.0f);
    else
        discard;
    return vec4(res / 255.0f, 1.0f);
}

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
    gl_FragColor = texture2D(tex, gl_PointCoord);
    gl_FragColor = rainbow(gl_PointCoord, vec2(0.5f, 0.5f));
}
