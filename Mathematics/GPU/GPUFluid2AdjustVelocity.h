// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <Mathematics/GPU/GPUFluid2Parameters.h>
#include <Graphics/GraphicsEngine.h>
#include <Graphics/ProgramFactory.h>
#include <Graphics/ConstantBuffer.h>
#include <Graphics/ProgramFactory.h>
#include <Graphics/Texture2.h>

namespace gte
{
    class GPUFluid2AdjustVelocity
    {
    public:
        // Construction.  Adjust the velocities using the solution to the
        // Poisson equation.
        GPUFluid2AdjustVelocity(std::shared_ptr<ProgramFactory> const& factory,
            int xSize, int ySize, int numXThreads, int numYThreads,
            std::shared_ptr<ConstantBuffer> const& parameters);

        // Update the state for the fluid simulation.
        void Execute(std::shared_ptr<GraphicsEngine> const& engine,
            std::shared_ptr<Texture2> const& inState,
            std::shared_ptr<Texture2> const& poisson,
            std::shared_ptr<Texture2> const& outState);

    private:
        int mNumXGroups, mNumYGroups;
        std::shared_ptr<ComputeProgram> mAdjustVelocity;

        // Shader source code as strings.
        static std::string const msGLSLSource;
        static std::string const msHLSLSource;
        static ProgramSources const msSource;
    };
}
