varying float alpha;
uniform float time;
attribute vec3 vertex;

float atten(float d)
{
    return 1.0/(0.001 + d*d);
}

vec3 calc_pos(vec3 initial, vec3 vel, float time)//верхняя позиция
{
    return initial + vel*time;
}

vec3 random_vector(float param)
{
    return vec3(sin(param), cos(param), sin(param) * exp(cos(param) * sin(param))); //cos(param*param), sin(param) * exp(cos(param) * sin(param)));
}

void main(void)
{


    vec3 rnd = random_vector(vertex.x);

    if (rnd.y > 0.94 || rnd.y < -0.94)
    {

        rnd.y=-1/0.2*cos(rnd.y*rnd.x*rnd.z);
    }

    vec3 pos = vec3(rnd.y, 1, 0.0); // нач позиция x берём из вектора rnd (вторую позицию), у=1, z=0
    vec3 vel = vec3(0, -20.0 * abs(rnd.x), 0.0);//скорость max(rnd.z,0.9)


    float t = fract((time + vertex.x) / (100.0 * 2.5));

    vec3 current_pos = calc_pos(pos, vel, t);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(current_pos, 1.0);
    alpha = 1.0 - t * t;
}
