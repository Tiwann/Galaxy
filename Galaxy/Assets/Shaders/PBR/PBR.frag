#version 450 core

in vec4 vcolor;
in vec2 texcoord;
out vec4 color;

uniform sampler2D albedo;
uniform sampler2D specular;
uniform sampler2D metallic;
uniform sampler2D roughness;
uniform sampler2D emissive;

void main() {
    color = texture(albedo, texcoord);
}