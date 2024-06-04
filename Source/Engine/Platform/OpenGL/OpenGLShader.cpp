#include "EnginePCH.h"
#include "OpenGLShader.h"

#include "Engine/Engine.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

GLfloat Vertices[] = {
    // Positions          // Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left-back
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right-back
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Top-right-back
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Top-left-back
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left-front
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right-front
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Top-right-front
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f   // Top-left-front
};

GLuint Indices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    0, 3, 7,
    7, 4, 0,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    0, 1, 5,
    5, 4, 0,
    // Top face
    3, 2, 6,
    6, 7, 3
};

void COpenGLShader::Compile()
{
    // Vertex Shader
    VertexShaderProgram->ShaderID = glCreateShader(GL_VERTEX_SHADER);
    const char* VertexShaderSource = VertexShaderProgram->Source.c_str();
    glShaderSource(VertexShaderProgram->ShaderID, 1, &VertexShaderSource, nullptr);
    glCompileShader(VertexShaderProgram->ShaderID);
    int32 VertexShaderCompileStatusFlags;
    glGetShaderiv(VertexShaderProgram->ShaderID, GL_COMPILE_STATUS, &VertexShaderCompileStatusFlags);
    if (!VertexShaderCompileStatusFlags)
    {
        char Log[512];
        glGetShaderInfoLog(VertexShaderProgram->ShaderID, 512, nullptr, Log);
        ASSERT(false, Log);
    }
    
    // Fragment Shader
    FragmentShaderProgram->ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* FragmentShaderSource = FragmentShaderProgram->Source.c_str();
    glShaderSource(FragmentShaderProgram->ShaderID, 1, &FragmentShaderSource, nullptr);
    glCompileShader(FragmentShaderProgram->ShaderID);
    int32 FragmentShaderCompileStatusFlags;
    glGetShaderiv(FragmentShaderProgram->ShaderID, GL_COMPILE_STATUS, &FragmentShaderCompileStatusFlags);
    if (!FragmentShaderCompileStatusFlags)
    {
        char Log[512];
        glGetShaderInfoLog(FragmentShaderProgram->ShaderID, 512, nullptr, Log);
        ASSERT(false, Log);
    }

    // Linking
    ShaderID = glCreateProgram();
    glAttachShader(ShaderID, VertexShaderProgram->ShaderID);
    glAttachShader(ShaderID, FragmentShaderProgram->ShaderID);
    glLinkProgram(ShaderID);
    int32 ShaderCompileStatusFlags;
    glGetProgramiv(ShaderID, GL_LINK_STATUS, &ShaderCompileStatusFlags);
    if (!ShaderCompileStatusFlags)
    {
        char Log[512];
        glGetProgramInfoLog(ShaderID, 512, nullptr, Log);
        ASSERT(false, Log);
    }

    glDeleteShader(VertexShaderProgram->ShaderID);
    glDeleteShader(FragmentShaderProgram->ShaderID);

    VAO = MakeUniquePtr<SVertexArrayObject>();
    VAO->Bind();

    VBO = MakeUniquePtr<SVertexBufferObject>(Vertices, sizeof(Vertices));
    IBO = MakeUniquePtr<SIndexBufferObject>(Indices, sizeof(Indices));
    
    VAO->LinkAttrib(*VBO.Get(), 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO->LinkAttrib(*VBO.Get(), 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO->Unbind();
    VBO->Unbind();
    IBO->Unbind();
}

void COpenGLShader::Use()
{
    glUseProgram(ShaderID);
}

void COpenGLShader::Render()
{
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(Indices), GL_UNSIGNED_INT, 0);
    VAO->Unbind();
}

void COpenGLShader::Delete()
{
    VAO->Delete();
    VBO->Delete();
    IBO->Delete();
    glDeleteProgram(ShaderID);
}

void COpenGLShader::SetVec3(const std::string& Name, const SVector3f& Vec3) const
{
    glUniform3f(glGetUniformLocation(ShaderID, Name.c_str()), Vec3.X, Vec3.Y, Vec3.Z);
}

void COpenGLShader::SetInt(const std::string& Name, int32 Value) const
{
    glUniform1i(glGetUniformLocation(ShaderID, Name.c_str()), Value);
}

void COpenGLShader::SetFloat(const std::string& Name, float Value) const
{
    glUniform1f(glGetUniformLocation(ShaderID, Name.c_str()), Value);
}

void COpenGLShader::SetBool(const std::string& Name, bool bValue) const
{
    glUniform1i(glGetUniformLocation(ShaderID, Name.c_str()), (int32)bValue);
}

void COpenGLShader::SetMat4(const char* str, const glm::mat4& Matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderID, str), 1, GL_FALSE, &Matrix[0][0]);
}
