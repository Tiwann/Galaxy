#version 460 core

in vec3 position;
in vec4 vcolor;
in vec2 texcoord;
in vec3 normal;
out vec4 color;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 cameraPos;

uniform sampler2D albedoMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;

void main() {
    
    vec4 albedo = texture(albedoMap, texcoord);
    float ambient = 0.1;

    vec4 normalTex = texture(normalMap, texcoord);
    vec4 specular = texture(specularMap, texcoord);
    
    vec3 nrm = mix(normalize(normal), normalTex.xyz, 0.5);
    vec3 lightDir = normalize(lightPos - position);
    float diffuse = max(dot(lightDir, nrm), 0.0);
   
    color = albedo * (lightColor + ambient);
}