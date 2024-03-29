// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <Mathematics/Delaunay2.h>

namespace gte
{
    template <typename InputType, typename ComputeType, typename RationalType>
    class Delaunay2Mesh
    {
    public:
        // Construction.
        Delaunay2Mesh(Delaunay2<InputType, ComputeType> const& delaunay)
            :
            mDelaunay(&delaunay)
        {
        }

        // Mesh information.
        inline int GetNumVertices() const
        {
            return mDelaunay->GetNumVertices();
        }

        inline int GetNumTriangles() const
        {
            return mDelaunay->GetNumTriangles();
        }

        inline Vector2<InputType> const* GetVertices() const
        {
            return mDelaunay->GetVertices();
        }

        inline int const* GetIndices() const
        {
            return &mDelaunay->GetIndices()[0];
        }

        inline int const* GetAdjacencies() const
        {
            return &mDelaunay->GetAdjacencies()[0];
        }

        // Containment queries.
        int GetContainingTriangle(Vector2<InputType> const& P) const
        {
            typename Delaunay2<InputType, ComputeType>::SearchInfo info;
            return mDelaunay->GetContainingTriangle(P, info);
        }

        bool GetVertices(int t, std::array<Vector2<InputType>, 3>& vertices) const
        {
            if (mDelaunay->GetDimension() == 2)
            {
                std::array<int, 3> indices;
                if (mDelaunay->GetIndices(t, indices))
                {
                    PrimalQuery2<ComputeType> const& query = mDelaunay->GetQuery();
                    Vector2<ComputeType> const* ctVertices = query.GetVertices();
                    for (int i = 0; i < 3; ++i)
                    {
                        Vector2<ComputeType> const& V = ctVertices[indices[i]];
                        for (int j = 0; j < 2; ++j)
                        {
                            vertices[i][j] = (InputType)V[j];
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        bool GetIndices(int t, std::array<int, 3>& indices) const
        {
            return mDelaunay->GetIndices(t, indices);
        }

        bool GetAdjacencies(int t, std::array<int, 3>& adjacencies) const
        {
            return mDelaunay->GetAdjacencies(t, adjacencies);
        }

        bool GetBarycentrics(int t, Vector2<InputType> const& P, std::array<InputType, 3>& bary) const
        {
            std::array<int, 3> indices;
            if (mDelaunay->GetIndices(t, indices))
            {
                PrimalQuery2<ComputeType> const& query = mDelaunay->GetQuery();
                Vector2<ComputeType> const* vertices = query.GetVertices();
                Vector2<RationalType> rtP{ P[0], P[1] };
                std::array<Vector2<RationalType>, 3> rtV;
                for (int i = 0; i < 3; ++i)
                {
                    Vector2<ComputeType> const& V = vertices[indices[i]];
                    for (int j = 0; j < 2; ++j)
                    {
                        rtV[i][j] = (RationalType)V[j];
                    }
                };

                RationalType rtBary[3];
                if (ComputeBarycentrics(rtP, rtV[0], rtV[1], rtV[2], rtBary))
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        bary[i] = (InputType)rtBary[i];
                    }
                    return true;
                }
            }
            return false;
        }

    private:
        Delaunay2<InputType, ComputeType> const* mDelaunay;
    };
}
