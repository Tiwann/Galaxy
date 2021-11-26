#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_texcoord;
layout(location = 2) in vec3 v_normal;
layout(location = 3) in vec4 v_color;


out vec2 texcoord;
out vec4 vcolor;

void main() {
    gl_Position = vec4(v_position, 1.0);
    vcolor = v_color;
    texcoord = v_texcoord;
}
