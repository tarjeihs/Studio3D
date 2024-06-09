#version 330 core

layout (location = 0) in vec3 aPos;     // Position attribute
layout (location = 1) in vec3 aNormal;  // Normal attribute
layout (location = 2) in vec2 aTexCoord; // Texture coordinate attribute
layout (location = 3) in vec3 aColor;   // Vertex color attribute

out vec3 FragPos;       // Output position to fragment shader
out vec3 Normal;        // Output normal to fragment shader
out vec2 TexCoord;      // Output texture coordinate to fragment shader
out vec3 VertexColor;   // Output vertex color to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));  // Calculate the fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal;  // Transform the normal vector to world space
    TexCoord = aTexCoord;  // Pass the texture coordinate to the fragment shader
    VertexColor = aColor;  // Pass the vertex color to the fragment shader

    gl_Position = projection * view * model * vec4(aPos, 1.0);  // Calculate the position of the vertex in clip space
}
