// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <Applications/Window3.h>
#include <Applications/Timer.h>
#include "PhysicsModule.h"
using namespace gte;

//#define FREE_TOP_FIXED_TIP_SINGLE_STEP

class FreeTopFixedTipWindow3 : public Window3
{
public:
    FreeTopFixedTipWindow3(Parameters& parameters);

    virtual void OnIdle() override;
    virtual bool OnCharPress(unsigned char key, int x, int y) override;

private:
    bool SetEnvironment();
    void InitializeModule();
    void CreateScene();
    void CreateFloor();
    void CreateAxisVertical();
    void CreateTop();
    void CreateAxisTop();
    void PhysicsTick();
    void GraphicsTick();

    // The scene graph.
    std::shared_ptr<Node> mScene, mTopRoot;
    std::shared_ptr<RasterizerState> mWireState;
    std::vector<std::shared_ptr<Visual>> mVisuals;

    // The physics system.
    PhysicsModule mModule;
    float mMaxPhi;

    // Support for clamping the frame rate.
    Timer mMotionTimer;
    double mLastUpdateTime;
};
