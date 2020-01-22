#pragma once
#include "DataMessage.hpp"
#include "Vector3D.hpp"
#include "PoseMsg.hpp"
#include "TaggedPoses.hpp"
#include <vector>

class TaggedPosesMsg : public DataMessage
{

public:

    TaggedPosesMsg();
    ~TaggedPosesMsg();
    msg_type getType();
    const int getSize();

    TaggedPoses tagged_poses;
};