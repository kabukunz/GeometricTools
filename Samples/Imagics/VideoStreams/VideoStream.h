// David Eberly, Geometric Tools, Redmond WA 98052
// Copyright (c) 1998-2019
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
// https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// Version: 4.0.2019.08.13

#pragma once

#include <Applications/Timer.h>
#include <Graphics/GraphicsEngine.h>

class VideoStream
{
public:
    // The class is abstract.  Derived classes must implement the pure virtual
    // function 'char* GetImage ()'.
    virtual ~VideoStream() = default;

    // Access to input information.
    inline std::shared_ptr<gte::GraphicsEngine> const& GetEngine() const
    {
        return mEngine;
    }

    inline gte::DFType GetType() const
    {
        return mType;
    }

    inline unsigned int GetWidth() const
    {
        return mWidth;
    }

    inline unsigned int GetHeight() const
    {
        return mHeight;
    }

    // A frame consists of a frame number (unique identifier), the image data
    // represented as a texture, and the time (in microseconds) to acquire the
    // image and copy it to GPU memory.
    struct Frame
    {
        Frame()
            :
            number(0xFFFFFFFF),
            microseconds(0)
        {
        }

        unsigned int number;
        std::shared_ptr<gte::Texture2> image;
        int64_t microseconds;
    };

    // Get the current frame.  The returned frame is a copy of the member
    // data so that the texture may be consumed at any time without fear
    // of the producer overwriting the member data with a new frame.
    inline Frame GetFrame() const
    {
        return mFrame;
    }

    // Support for production of a single frame.  The function assigns values
    // to the current frame.  It returns 'true' iff the production was
    // successful (a malformed file can lead to a failed read of data).
    void CaptureFrame();

    // Performance measurements.  These are accumulated measurements starting
    // from a call to ResetPerformanceMeasurements().
    void ResetPerformanceMeasurements();

    inline unsigned int GetPerformanceFrames() const
    {
        return mPerformanceFrames;
    }

    inline int64_t GetPerformanceMicroseconds() const
    {
        return mPerformanceMicroseconds;
    }

    double GetFramesPerSecond() const;
    double GetSecondsPerFrame() const;

protected:
    // Constructor used by derived classes.
    VideoStream(std::shared_ptr<gte::GraphicsEngine> const& engine);

    // A derived class must implement this function for its image capture
    // mechanism.  The function returns the image that is consumed in the
    // 'void CaptureFrame ()' call.
    virtual char* GetImage() = 0;

    // The engine that is used to upload textures to GPU memory and the
    // texture information.  The derived class must see these four members.
    std::shared_ptr<gte::GraphicsEngine> mEngine;
    gte::DFType mType;
    unsigned int mWidth;
    unsigned int mHeight;

    // The current frame.  The timer is used to compute how long it takes to
    // produce the frame.
    Frame mFrame;
    gte::Timer mProductionTimer;

    // Performance measurements.
    gte::Timer mPerformanceTimer;
    unsigned int mPerformanceFrames;
    int64_t mPerformanceMicroseconds;
};
