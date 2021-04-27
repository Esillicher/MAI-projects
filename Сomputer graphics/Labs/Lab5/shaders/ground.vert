attribute vec3 qt_Vertex;
attribute vec3 qt_Normal;

varying vec3 position;
uniform mat4 mvp;

const vec3 lightdir = vec3(3.0, 4.0, 5.0);
varying float lightcolor;

void main(void)
{
    position = qt_Vertex.xyz;
    lightcolor = dot(normalize(qt_Normal), normalize(lightdir));
    gl_Position = mvp * vec4(qt_Vertex, 1.0);
}
