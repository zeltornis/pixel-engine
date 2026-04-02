#version 330 core
in vec3 vertexColor; // from vertex shader

uniform float uTime;
uniform vec2 uResolution;

out vec4 FragColor;

void main()
{
    vec2 xy = gl_FragCoord.xy;
    vec2 uv = xy / uResolution.xy;
    FragColor = vec4(uv, 0.0, 1.0);
}