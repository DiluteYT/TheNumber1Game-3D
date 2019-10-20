#shader vertex

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in mat4 InstancedModel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool instanced;

out vec2 TexCoord;
out vec3 f_color;

void main()
{
	if (instanced)
		gl_Position = projection * view * InstancedModel * vec4(position, 1.0f);
	else
		gl_Position = projection * view * model * vec4(position, 1.0f);
	f_color = v_color;
	TexCoord = aTexCoord;
}

#shader fragment

#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 f_color;

uniform sampler2D texture1511;

void main()
{
	FragColor = texture(texture1511, TexCoord) * vec4(f_color, 1.0f);
}