// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <Graphics/Texture2.h>

namespace gte
{
    class TextureDS : public Texture2
    {
    public:
        // Construction for depth-stencil textures.
        TextureDS(DFType format, unsigned int width, unsigned int height, bool createStorage = true);

        inline void MakeShaderInput()
        {
            mShaderInput = true;
        }

        inline bool IsShaderInput() const
        {
            return mShaderInput;
        }

    private:
        bool mShaderInput;
    };
}
