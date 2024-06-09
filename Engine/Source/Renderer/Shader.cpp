#include "EnginePCH.h"
#include "Shader.h"

#include <fstream>
#include <sstream>

#include "Core/Engine.h"

bool CShader::LoadSourceFile(const EShaderType ShaderType, const char* FilePath)
{
    std::ifstream File;
    File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        File.open(FilePath);
        std::stringstream FileBuffer;
        FileBuffer << File.rdbuf();
        File.close();

        switch (ShaderType)
        {
            case EShaderType::Vertex: { VertexShaderProgram->Source = FileBuffer.str(); break; };
            case EShaderType::Fragment: { FragmentShaderProgram->Source = FileBuffer.str(); break; };
        }
        
        return true;
    }
    catch (std::ifstream::failure&)
    {
        ASSERT(false, "File was not successfully read.");
    }
    return false;
}
