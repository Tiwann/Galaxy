#version 450 core

in vec4 vcolor;
in vec2 texcoord;
out vec4 color;

const float PI = 3.14159265359;

uniform sampler2D m_albedo;
uniform sampler2D m_specular;
uniform sampler2D m_metallic;
uniform sampler2D m_roughness;
uniform sampler2D m_emissive;

uniform vec3  albedo;
uniform float specular;
uniform float metallic;
uniform float roughness;
uniform vec3  emissive;


float ggx_distrib(vec3 n, vec3 h, float a) 
{
    float a2 = a * a;
    float ndoth = dot(n, h);
    float ndoth2 = ndoth * ndoth;
    float denom = PI * pow(ndoth2 * (a2 - 1.0) + 1.0, 2);
    return a2 / max(denom, 0.000001);
}

float schlick_ggx(vec3 n, vec3 v, float k)
{
    float ndotv = dot(n, v);
	return ndotv / max((ndotv * (1.0 - k) + k), 0.000001);
}

float smith(vec3 n, vec3 v, vec3 l, float a)
{
    float r = a + 1.0;
    float k = pow(r, 2) / 8.0;
    float ggx1 = schlick_ggx(n, v, k);
    float ggx2 = schlick_ggx(n, l, k);
    return ggx1 * ggx2;
}


void main() 
{
    color = texture(m_albedo, texcoord);
}