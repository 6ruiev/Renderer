#shader vertex 

#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 vertexColor;
uniform float x_offset;
void main()
{
   gl_Position = vec4(x_offset + aPos.x, -aPos.y, aPos.z, 1.0);
   vertexColor = aPos;
};


#shader fragment

#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
void main()
{
	FragColor = vec4(vertexColor, 1.0);
};
