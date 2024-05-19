#version 330 core

layout(location = 0) in vec4 position;
// layout(location = 1) in vec2 textCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 camera;


void main()
{
    // v_TextCoord = textCoord;
    gl_Position = proj * camera * view * model * position;
}
;

