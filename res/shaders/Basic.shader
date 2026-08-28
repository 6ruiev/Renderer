#shader vertex 

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoor;

out vec3 vertexColor;
out vec2 texCoor;

uniform float x_offset;
uniform float y_offset;

void main()
{
   gl_Position = vec4(x_offset + aPos.x, y_offset + -aPos.y, aPos.z, 1.0);
   vertexColor = aColor;
   texCoor = aTexCoor;
};


#shader fragment

#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, texCoor);
};
