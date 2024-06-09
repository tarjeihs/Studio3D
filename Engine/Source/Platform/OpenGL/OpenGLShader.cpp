#include "EnginePCH.h"
#include "OpenGLShader.h"

#include "Core/Engine.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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
}

void COpenGLShader::Use()
{
    glUseProgram(ShaderID);

    for (auto& Pair : BoolParameterMap)
    {
        if (Pair.second == true)
        {
            SetBool(Pair.first, Pair.second);
        }
    }
}

void COpenGLShader::Delete()
{
    glDeleteProgram(ShaderID);
}

void COpenGLShader::SetVector3(const std::string& Name, const glm::vec3& Vec3) const
{
    glUniform3f(glGetUniformLocation(ShaderID, Name.c_str()), Vec3.x, Vec3.y, Vec3.z);
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

void COpenGLShader::SetMat4(const std::string& Name, const glm::mat4& Matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderID, Name.c_str()), 1, GL_FALSE, &Matrix[0][0]);
}

void COpenGLShader::SetVec4(const std::string& Name, const glm::vec4& Vec4) const
{
    glUniform4f(glGetUniformLocation(ShaderID, Name.c_str()), Vec4.x, Vec4.y, Vec4.z, Vec4.w);
}
