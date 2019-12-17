// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

Texture2D<float4> weights;
RWTexture2D<int2> previous;
RWTexture2D<float> sum;

[numthreads(ISIZE, 1, 1)]
void CSMain(int diagonal : SV_GroupThreadID)
{
    previous[int2(diagonal, 0)] = int2(diagonal - 1, 0);
    sum[int2(diagonal, diagonal)] = weights[int2(diagonal, 0)].y;
}
