#version 460 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texcoord;
layout(location = 2) in vec3 v_normal;
layout(location = 3) in vec4 v_color;

out vec2 texcoord;
out vec3 normal;
out vec4 vcolor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main() {
    gl_Position = projection * view * model * vec4(v_position, 1.0);
    vcolor = v_color;
    texcoord = v_texcoord;
    normal = v_normal;
}
