# Complex Shaders

In this project, I attempt to learn from various open source shaders online, and hopefully construct my own. Many of these shaders can be found on [the book of shaders][BOOK_OF_SHADERS]. These shaders are ones I've found particularly interesting and have decided to showcase:



## Shaders made by other people



### Gradient Shader

```glsl
#version 330 core

uniform vec2 u_resolution;

float plot(vec2 st) {    
    return smoothstep(0.01, 0.0, abs(st.y - st.x));
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_resolution;

    float y = st.x;
    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st);
    color = (1.0-pct)*color+pct*vec3(0.0,1.0,0.0);

    FragColor = vec4(color, 1.0f);
}
```

<img src="Documentation\Sourced Shaders\1.PNG" alt="1"  />



### Noise Shader

```glsl
// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com

#version 330 core

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
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
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    st.x += u_time*0.25;

    vec3 color = vec3(0.0);
    color += fbm(st*3.0);

    FragColor = vec4(color,1.0);
}
```

<img src="Documentation\Sourced Shaders\2.gif" alt="2"  />



### Noise Shader with Domain Distortion

```glsl
// Author @patriciogv - 2015
// http://patriciogonzalezvivo.com

#version 330 core

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
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

// DISTORTION FUNCTION iquilezles.org/articles/warp/
float distortion( in vec2 p )
{
    vec2 q = vec2( fbm( p + vec2(0.0,0.0) ),
                   fbm( p + vec2(5.2,1.3) ) );

    vec2 r = vec2( fbm( p + 4.0*q + vec2(1.7,9.2) ),
                   fbm( p + 4.0*q + vec2(8.3,2.8) ) );

    return fbm( p + 4.0*r );
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    st.y -= u_time*0.25;

    float pixel_multiplier = 1.0f;
    st *= pixel_multiplier;

    vec3 red = vec3(0.9f, 0.2f, 0.1f);

    vec3 color = vec3(0.0);
    color += distortion(st*3.0);
    color *= red;

    FragColor = vec4(color,1.0);
}
```

<img src="Documentation\Sourced Shaders\3.gif" alt="3"  />





## Shaders I made

Most of these shaders are shaders made by others that I tweaked. I believe I tweaked them enough to the point where they are arguably different.



### Fire Shader

```glsl
// Vertex Shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float color;

out float aColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    aColor = color;
}

/* --------------------------------------------------------------------------- */

// Fragment Shader
#version 330 core

out vec4 FragColor;
in float aColor;

uniform vec2 u_resolution;
uniform float u_time;

float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
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

float distortion( in vec2 p )
{
    vec2 q = vec2( fbm( p + vec2(0.0,0.0) ),
                   fbm( p + vec2(5.2,1.3) ) );

    vec2 r = vec2( fbm( p + 4.0*q + vec2(1.7,9.2) ),
                   fbm( p + 4.0*q + vec2(8.3,2.8) ) );

    return fbm( p + 4.0*r ) * 18.0f + sin(u_time*0.3) * 3.0f;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    st.y -= u_time*0.7;

    float pixel_multiplier = 1.0f;
    st *= pixel_multiplier;

    vec3 red = vec3(0.9f, 0.2f, 0.1f);

    vec3 color = vec3(0.0);
    color += distortion(st*3.0);
    color *= red * aColor;

    FragColor = vec4(color,1.0);
}
```

<img src="Documentation\Created Shaders\fire.gif" alt="fire"  />



### Mouse Curser Shader

```glsl
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
```

<img src="Documentation\Created Shaders\mouse shader.gif" alt="mouse shader"  />







[BOOK_OF_SHADERS]: https://thebookofshaders.com