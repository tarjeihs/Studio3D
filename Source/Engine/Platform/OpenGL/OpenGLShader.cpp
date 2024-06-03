#include "EnginePCH.h"
#include "OpenGLShader.h"

#include "Engine/Engine.h"

GLfloat Vertices[] = {
    // Positions        // Colors
    0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top Right
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom Right
   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Bottom Left
   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  // Top Left 
};

GLuint Indices[] = {
    0, 1, 3, // First Triangle
    1, 2, 3  // Second Triangle
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

void COpenGLShader::Render()
{
    glUseProgram(ShaderID);
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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