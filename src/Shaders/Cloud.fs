#version 330 core

in vec2 vTex;
out vec4 FragColor;

void main() {
    float alpha = smoothstep(1.0, 0.5, length(vTex - 0.5)); 
    FragColor = vec4(1.0, 1.0, 1.0, alpha * 0.5); 
}