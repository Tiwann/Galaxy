#version 450 core

in vec4 vcolor;
in vec2 texcoord;
out vec4 color;

uniform sampler2D tex0;

void main() {
    color = texture(tex0, texcoord);
}