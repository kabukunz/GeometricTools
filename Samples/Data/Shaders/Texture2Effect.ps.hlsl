// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

Texture2D baseTexture;
SamplerState baseSampler;

struct PS_INPUT
{
    float2 vertexTCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 pixelColor : SV_TARGET0;
};

PS_OUTPUT PSMain(PS_INPUT input)
{
    PS_OUTPUT output;
    output.pixelColor = baseTexture.Sample(baseSampler, input.vertexTCoord);
    return output;
}
