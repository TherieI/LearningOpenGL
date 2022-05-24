#version 330 core

out vec4 FragColor;

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(43.2442,33.233)))*
        46388.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

#define OCTAVES 6
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    float pct = 0.0;

    vec2 mouse_pos = vec2(u_mouse.x/u_resolution.x, -u_mouse.y/u_resolution.y + 1.0f);  // getting the relative mouse position

    // a. The DISTANCE from the pixel to the center
    pct = distance(st, mouse_pos)*10.0f;

    vec3 color = vec3(pct) * fbm(st);
    color = vec3(1.0f) - color; // inverse color
    color *= vec3(0.8f, 0.3f, 0.1f);

    FragColor = vec4(color, 1.0f);
}