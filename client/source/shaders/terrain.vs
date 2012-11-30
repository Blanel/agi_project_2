#version 410

uniform mat4 r_MVP = mat4(1.0);
//uniform mat4 r_ModelView = mat4(1.0);

layout(location = 0) in vec3 in_VtxPosition;
layout(location = 1) in vec3 in_VtxNormal;
layout(location = 2) in vec2 in_TexCoord0;

//out vec3 Position;
//out vec3 Normal;
out vec2 UV;


void main()
{
	//Position = vec3(r_ModelView * vec4(in_VtxPosition, 1.0));
	//Normal = vec3(r_ModelView * vec4(in_VtxNormal, 0.0));	
	UV = in_TexCoord0;

    gl_Position = r_MVP * vec4(in_VtxPosition, 1.0);
}
