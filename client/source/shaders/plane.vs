#version 410

uniform mat4 r_MVP = mat4(1.0);

in vec3 in_VtxPosition;

void main()
{
    gl_Position = r_MVP * vec4(in_VtxPosition, 1.0);
}
