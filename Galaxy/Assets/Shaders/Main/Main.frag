#version 450 core

in vec4 vcolor;
in vec2 texcoord;
out vec4 color;

uniform sampler2D albedo;

void main() {
    color = texture(albedo, texcoord);
}