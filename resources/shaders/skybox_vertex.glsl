#version 410 core
layout (location = 0) in vec3 position;

out vec3 texture_coord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    texture_coord = vec3(position.x, -position.y, -position.z);
    gl_Position = projection * view * vec4(position, 1.0);
}
