#include "EnginePCH.h"
#include "MaterialInstance.h"

void CMaterialInstance::Bind()
{
    // Reset Index to 0
    TextureIndexCounter = 0;
    
    BaseMaterial->Bind();
    for (auto& [Name, Uniform] : Uniforms)
    {
        UploadUniformToGPU(Name, Uniform);
    }
}

void CMaterialInstance::UploadUniformToGPU(const std::string& Name, const SUniform& Uniform)
{
    int32 Location = glGetUniformLocation(BaseMaterial->GetShader()->GetShaderID(), Name.c_str());
    if (Location == -1) return;

    switch (Uniform.Type)
    {
        case EUniformType::Vec2:        glUniform2fv(Location, 1, glm::value_ptr(Uniform.Vec2Value)); break;
        case EUniformType::Vec3:        glUniform3fv(Location, 1, glm::value_ptr(Uniform.Vec3Value)); break;
        case EUniformType::Vec4:        glUniform4fv(Location, 1, glm::value_ptr(Uniform.Vec4Value)); break;
        case EUniformType::Mat3:        glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(Uniform.Mat3Value)); break;
        case EUniformType::Mat4:        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Uniform.Mat4Value)); break;
        case EUniformType::Float:       glUniform1f(Location, Uniform.FloatValue); break;
        case EUniformType::Int:         glUniform1i(Location, Uniform.IntValue); break;
        case EUniformType::Bool:        glUniform1i(Location, Uniform.BoolValue); break;
        case EUniformType::Sampler2D:
        {
            glUniform1i(Location, TextureIndexCounter);
            Uniform.Texture2DValue->Bind(TextureIndexCounter);
            TextureIndexCounter++;
        }
    }
}

