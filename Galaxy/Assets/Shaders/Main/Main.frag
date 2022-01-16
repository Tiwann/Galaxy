#version 460 core

in vec4 vcolor;
in vec2 texcoord;
in vec3 normal;
out vec4 color;

uniform sampler2D albedo;

void main() {
    //output albedo color
    color = texture(albedo, texcoord);

    //output normals;
    //color = vec4(normal, 1.0);

    //output texture coordinates;
    //color = vec4(texcoord, 0.0, 1.0);
}