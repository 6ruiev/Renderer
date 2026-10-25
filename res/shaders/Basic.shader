#shader vertex 

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform float x_offset;
uniform float y_offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   // 0
   gl_Position = projection * view * model * vec4(x_offset + aPos.x, y_offset + aPos.y, aPos.z, 1.0);

   // 1
   vertexColor = aColor;

   // 2
   texCoord = aTexCoord;
};


#shader fragment

#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform float mixValue;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = mix( texture(texture0, texCoord), texture(texture1, texCoord), mixValue );
};
