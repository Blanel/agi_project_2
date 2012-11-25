#version 400


uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
/*
uniform mat4 r_ProjMatrix = mat4(1.303, 0.0, 0.0, 0.0,
                                 0.0, 0.977419, 0.0, 0.0,
                                 0.0, 0.0, -1.002, -0.2002,
                                 0.0, 0.0, -1.0, 1.0
                                 );
*/
uniform mat4 ProjMatrix;
uniform mat4 r_MVP = mat4(1.0);

in vec3 in_VtxPosition;

void main()
{
    gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4(in_VtxPosition, 1.0);
}
