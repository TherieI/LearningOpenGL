#version 430
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(r32f, binding = 0) uniform image2D out_image;

void main() {
   // get position to read/write data from
    ivec2 pixel_coord = ivec2( gl_GlobalInvocationID.xy );

    // get value stored in the image
    float in_val = imageLoad( out_image, pixel_coord ).r;

    // store new value in image
    imageStore( out_image, pixel_coord, vec4( 2.0f, 0.0, 0.0, 0.0 ) );
}