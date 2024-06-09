#include "EnginePCH.h"
#include "PrimitiveMeshComponent.h"

#include <array>
#include <span>

#include "Renderer/Mesh.h"

constexpr float PARAMETER_SPHERE_RADIUS         =   1.0f;
constexpr uint32 PARAMETER_SPHERE_RINGS         =    16;
constexpr uint32 PARAMETER_SPHERE_SECTORS       =    32;

constexpr float PARAMETER_CAPSULE_RADIUS =        0.25f;
constexpr float PARAMETER_CAPSULE_HALFHEIGHT =    0.2f;
constexpr uint32 PARAMETER_CAPSULE_RINGS =         20;
constexpr uint32 PARAMETER_CAPSULE_SECTORS =       20;

void CPrimitiveComponent::SetPrimitiveTypeCube()
{
    static std::vector<glm::vec3> Vertices = {
        // Front face
        { -0.5f, -0.5f,  0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f },
        // Back face
        { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { -0.5f,  0.5f, -0.5f },
        // Left face
        { -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f, -0.5f },
        // Right face
        { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f,  0.5f }, { 0.5f,  0.5f,  0.5f }, { 0.5f,  0.5f, -0.5f },
        // Top face
        { -0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f, -0.5f }, { 0.5f,  0.5f,  0.5f }, { -0.5f,  0.5f,  0.5f },
        // Bottom face
        { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f,  0.5f }, { -0.5f, -0.5f,  0.5f }
    };

    static std::vector<glm::vec3> Normals = {
        // Front face
        { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f },
        // Back face
        { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, -1.0f },
        // Left face
        { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f },
        // Right face
        { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
        // Top face
        { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
        // Bottom face
        { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }
    };

    static std::vector<glm::vec2> TexCoords = {
        // Front face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
        // Back face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
        // Left face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
        // Right face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
        // Top face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
        // Bottom face
        { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f }
    };

    static std::vector<uint32> Indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 6, 5, 6, 4, 7,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 14, 13, 14, 12, 15,
        // Top face
        16, 18, 17, 18, 16, 19,
        // Bottom face
        20, 21, 22, 22, 23, 20
    };
    
    Mesh->UploadAssetData(Vertices, Normals, TexCoords, Indices);
}

void CPrimitiveComponent::SetPrimitiveTypeSphere()
{
    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> TexCoords;
    std::vector<uint32> Indices;
    
    for (uint32 R = 0; R <= PARAMETER_SPHERE_RINGS; ++R)
    {
        for (uint32 S = 0; S <= PARAMETER_SPHERE_SECTORS; ++S)
        {
            float X = cos(2.0f * PI * S / PARAMETER_SPHERE_SECTORS) * sin(PI * R / PARAMETER_SPHERE_RINGS);
            float Y = sin(-PI / 2.0f + PI * R / PARAMETER_SPHERE_RINGS);
            float Z = sin(2.0f * PI * S / PARAMETER_SPHERE_SECTORS) * sin(PI * R / PARAMETER_SPHERE_RINGS);

            glm::vec3 vertex = glm::vec3(X, Y, Z) * PARAMETER_SPHERE_RADIUS;
            glm::vec3 normal = glm::normalize(glm::vec3(X, Y, Z));
            glm::vec2 texCoord = glm::vec2((float)S / PARAMETER_SPHERE_SECTORS, (float)R / PARAMETER_SPHERE_RINGS);

            Vertices.push_back(vertex);
            Normals.push_back(normal);
            TexCoords.push_back(texCoord);
        }
    }

    for (uint32 R = 0; R < PARAMETER_SPHERE_RINGS; ++R)
    {
        for (uint32 S = 0; S < PARAMETER_SPHERE_SECTORS; ++S)
        {
            uint32 First = R * (PARAMETER_SPHERE_SECTORS + 1) + S;
            uint32 Second = First + PARAMETER_SPHERE_SECTORS + 1;

            Indices.push_back(First);
            Indices.push_back(Second);
            Indices.push_back(First + 1);

            Indices.push_back(Second);
            Indices.push_back(Second + 1);
            Indices.push_back(First + 1);
        }
    }

    Mesh->UploadAssetData(Vertices, Normals, TexCoords, Indices);
}

void CPrimitiveComponent::SetPrimitiveTypeCapsule()
{
    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> TexCoords;
    std::vector<uint32> Indices;
    
    // Top Hemisphere
    for (unsigned int r = 0; r <= PARAMETER_CAPSULE_RINGS / 2; ++r) {
        for (unsigned int s = 0; s <= PARAMETER_CAPSULE_SECTORS; ++s) {
            float y = -sin(-PI / 2.0f + PI * r / PARAMETER_CAPSULE_RINGS);
            float x = -cos(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS) * sin(PI * r / PARAMETER_CAPSULE_RINGS);
            float z = -sin(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS) * sin(PI * r / PARAMETER_CAPSULE_RINGS);
    
            glm::vec3 vertex = glm::vec3(x, y + 0.4f, z) * PARAMETER_CAPSULE_RADIUS;
            vertex.y += PARAMETER_CAPSULE_HALFHEIGHT; // Move top hemisphere to the top
    
            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
            glm::vec2 texCoord = glm::vec2((float)s / PARAMETER_CAPSULE_SECTORS, (float)r / PARAMETER_CAPSULE_RINGS);
    
            Vertices.push_back(vertex);
            Normals.push_back(normal);
            TexCoords.push_back(texCoord);
        }
    }

    // Cylinder Body
    for (unsigned int r = 0; r <= PARAMETER_CAPSULE_RINGS; ++r) {
        for (unsigned int s = 0; s <= PARAMETER_CAPSULE_SECTORS; ++s) {
            float y = -1.0f + 2.0f * r / PARAMETER_CAPSULE_RINGS; // From -1 to 1
            float x = cos(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS);
            float z = sin(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS);

            glm::vec3 vertex = glm::vec3(x, y, z) * PARAMETER_CAPSULE_RADIUS;
            vertex.y *= PARAMETER_CAPSULE_HALFHEIGHT; // Scale height to half-height
            vertex.y += (y > 0.0f ? PARAMETER_CAPSULE_RADIUS : -PARAMETER_CAPSULE_RADIUS); // Adjust top and bottom parts

            glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));
            glm::vec2 texCoord = glm::vec2((float)s / PARAMETER_CAPSULE_SECTORS, 0.5f + (float)r / PARAMETER_CAPSULE_RINGS * 0.5f);

            Vertices.push_back(vertex);
            Normals.push_back(normal);
            TexCoords.push_back(texCoord);
        }
    }

    // Bottom Hemisphere
    for (unsigned int r = 0; r <= PARAMETER_CAPSULE_RINGS / 2; ++r) {
        for (unsigned int s = 0; s <= PARAMETER_CAPSULE_SECTORS; ++s) {
            float y = sin(-PI / 2.0f + PI * r / PARAMETER_CAPSULE_RINGS);
            float x = cos(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS) * sin(PI * r / PARAMETER_CAPSULE_RINGS);
            float z = sin(2.0f * PI * s / PARAMETER_CAPSULE_SECTORS) * sin(PI * r / PARAMETER_CAPSULE_RINGS);

            glm::vec3 vertex = glm::vec3(x, y - 0.4f, z) * PARAMETER_CAPSULE_RADIUS;
            vertex.y -= PARAMETER_CAPSULE_HALFHEIGHT; // Move bottom hemisphere to the bottom

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
            glm::vec2 texCoord = glm::vec2((float)s / PARAMETER_CAPSULE_SECTORS, (float)(r + PARAMETER_CAPSULE_RINGS / 2) / PARAMETER_CAPSULE_RINGS);

            Vertices.push_back(vertex);
            Normals.push_back(normal);
            TexCoords.push_back(texCoord);
        }
    }

    // Indices for the top hemisphere
    for (unsigned int r = 0; r < PARAMETER_CAPSULE_RINGS / 2; ++r) {
        for (unsigned int s = 0; s < PARAMETER_CAPSULE_SECTORS; ++s) {
            unsigned int first = r * (PARAMETER_CAPSULE_SECTORS + 1) + s;
            unsigned int second = first + PARAMETER_CAPSULE_SECTORS + 1;
    
            Indices.push_back(first);
            Indices.push_back(first + 1);
            Indices.push_back(second);

            Indices.push_back(second);
            Indices.push_back(first + 1);
            Indices.push_back(second + 1);
        }
    }

    // Indices for the cylinder body
    unsigned int Offset = (PARAMETER_CAPSULE_RINGS / 2 + 1) * (PARAMETER_CAPSULE_SECTORS + 1);
    for (unsigned int r = 0; r < PARAMETER_CAPSULE_RINGS; ++r) {
        for (unsigned int s = 0; s < PARAMETER_CAPSULE_SECTORS; ++s) {
            unsigned int first = Offset + r * (PARAMETER_CAPSULE_SECTORS + 1) + s;
            unsigned int second = first + PARAMETER_CAPSULE_SECTORS + 1;

            Indices.push_back(first);
            Indices.push_back(second);
            Indices.push_back(first + 1);
            
            Indices.push_back(second);
            Indices.push_back(second + 1);
            Indices.push_back(first + 1);
        }
    }

    // Indices for the bottom hemisphere
    Offset += (PARAMETER_CAPSULE_RINGS + 1) * (PARAMETER_CAPSULE_SECTORS + 1);
    for (unsigned int r = 0; r < PARAMETER_CAPSULE_RINGS / 2; ++r) {
        for (unsigned int s = 0; s < PARAMETER_CAPSULE_SECTORS; ++s) {
            unsigned int first = Offset + r * (PARAMETER_CAPSULE_SECTORS + 1) + s;
            unsigned int second = first + PARAMETER_CAPSULE_SECTORS + 1;

            Indices.push_back(first);
            Indices.push_back(second);
            Indices.push_back(first + 1);
                       
            Indices.push_back(second);
            Indices.push_back(second + 1);
            Indices.push_back(first + 1);
        }
    }
    
    Mesh->UploadAssetData(Vertices, Normals, TexCoords, Indices);
}