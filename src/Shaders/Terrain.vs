#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out float vHeight;
out vec3  vWorldPos;  

void main() {
    vec4 worldPos = u_Model * vec4(aPos, 1.0);
    vWorldPos = worldPos.xyz;
    vHeight   = worldPos.y;
    gl_Position = u_Projection * u_View * worldPos;
}