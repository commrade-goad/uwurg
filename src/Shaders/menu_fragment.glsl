#version 330

out vec4 fragColor;

void main() {
    // Vibrant orange and purple colors
    vec3 orangeColor = vec3(1.0, 0.6, 0.0);   // Brighter orange
    vec3 purpleColor = vec3(0.7, 0.0, 1.0);   // More vibrant purple

    // Calculate position along the 45-degree angle
    vec2 normalizedCoord = gl_FragCoord.xy / vec2(1280.0, 720.0);
    float gradientPosition = (normalizedCoord.x + normalizedCoord.y) / 2.0;

    // Add a slight power function to make the gradient more interesting
    gradientPosition = pow(gradientPosition, 1.2);

    // Mix the colors based on the position
    vec3 finalColor = mix(purpleColor, orangeColor, gradientPosition);

    // Output the final color
    fragColor = vec4(finalColor, 1.0);
}
