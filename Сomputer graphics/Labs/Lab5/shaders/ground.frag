varying vec3 position;
varying float lightcolor;

uniform sampler2D sampler;

void main(void)
{
    vec3 diffColor = texture2D(sampler, position.xy).xyz;
    gl_FragColor = vec4(lightcolor * diffColor, 1.0);
}
