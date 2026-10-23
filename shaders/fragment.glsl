#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D u_texture;          // NOUVEAU : le "tiroir" où lire

void main() {
    float shade = 0.2 + (float(gl_PrimitiveID % 8) / 15.0);
    // FragColor = vec4(shade, shade, shade, 1.0);
    // FragColor = vec4(vUV, 0.0, 1.0);
    FragColor = texture(u_texture, vUV);   // NOUVEAU : couleur de l'image à la position vUV
}