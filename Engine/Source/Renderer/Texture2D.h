#pragma once

#include <glad/glad.h>

#include "Math/MathTypes.h"

class CTexture2D
{
public:
    CTexture2D()
    {
        glGenTextures(1, &TextureID);
    }

    ~CTexture2D()
    {
        glDeleteTextures(1, &TextureID);
    }

    void Bind(uint8 Unit)
    {
        glActiveTexture(GL_TEXTURE0 + Unit);
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }
    
    inline uint32 GetTextureID() const
    {
        return TextureID;
    }
    
private:
    int32 Width, Height, Channels;
    uint32 TextureID;

    friend class CAssetManager;
};
