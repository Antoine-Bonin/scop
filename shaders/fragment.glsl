#version 330 core
out vec4 FragColor;

void main() {
    // Modulo 8 pour avoir 8 nuances, divisé par 15 pour ne pas que ce soit trop blanc
    float shade = 0.2 + (float(gl_PrimitiveID % 8) / 15.0); 
    
    FragColor = vec4(shade, shade, shade, 1.0);
}