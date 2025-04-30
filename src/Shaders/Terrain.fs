#version 330 core

in float vHeight;
in vec3  vWorldPos;

out vec4 FragColor;

uniform float waterLevel;  
uniform float sandLevel;   
uniform float grassLevel;  
uniform float rockLevel;   
uniform float snowLevel;   

uniform float u_Time;
uniform vec3  u_CameraPos;

float hash(in vec2 p) {
    return fract(sin(dot(p, vec2(127.1,311.7))) * 43758.5453123);
}

void main() {
    vec3 color;

    if (vHeight < waterLevel) {
        vec3 baseColor = vec3(0.0, 0.1, 0.4);

        vec2 cell = floor(vWorldPos.xz * 0.2);
        float phaseX = hash(cell + 0.13) * 6.2831;
        float phaseZ = hash(cell + 0.57) * 6.2831;
        float ampX   = mix(0.15, 0.30, hash(cell + 0.29));
        float ampZ   = mix(0.15, 0.30, hash(cell + 0.83));

        float waveX = sin((vWorldPos.x * 0.5 + u_Time * 1.2) + phaseX) * ampX;
        float waveZ = sin((vWorldPos.z * 0.7 - u_Time * 0.8) + phaseZ) * ampZ;
        float wave  = (waveX + waveZ) * 1.5;

        float glow = pow(abs(wave), 5.0);
        vec3 highlight = vec3(1.0) * glow * 0.5;

        float depthFactor = clamp((waterLevel - vHeight) / 5.0, 0.0, 1.0);
        vec3 depthColor   = mix(vec3(0.0,0.2,0.4), baseColor, depthFactor);

        float fresnel     = pow(1.0 - dot(normalize(u_CameraPos - vWorldPos), vec3(0,1,0)), 3.0);
        vec3 fresnelColor = vec3(1.0) * fresnel * 0.3;

        float edgePulse = sin(u_Time * 4.0 + vWorldPos.x * 0.5) * 0.05;
        float alpha     = clamp(0.6 + edgePulse, 0.4, 1.0);

        color = baseColor;
        color = mix(color, depthColor, 0.5);
        color += highlight + fresnelColor;
        FragColor = vec4(color, alpha);
        return;
    }

    if (vHeight < sandLevel) {
        float t = (vHeight - waterLevel) / (sandLevel - waterLevel);
        color = mix(vec3(0.0,0.1,0.4), vec3(0.9,0.8,0.3), t);
        FragColor = vec4(color,1.0);
        return;
    }

    if (vHeight < grassLevel) {
        float t = (vHeight - sandLevel) / (grassLevel - sandLevel);
        color = mix(vec3(0.9,0.8,0.3), vec3(0.1,0.6,0.2), t);
        FragColor = vec4(color,1.0);
        return;
    }

    if (vHeight < rockLevel) {
        float t = (vHeight - grassLevel) / (rockLevel - grassLevel);
        color = mix(vec3(0.1,0.6,0.2), vec3(0.5,0.5,0.5), t);
        FragColor = vec4(color,1.0);
        return;
    }

    if (vHeight < snowLevel) {
        float t = (vHeight - rockLevel) / (snowLevel - rockLevel);
        color = mix(vec3(0.5,0.5,0.5), vec3(1.0,1.0,1.0), t);
        FragColor = vec4(color,1.0);
        return;
    }

    FragColor = vec4(1.0);
}