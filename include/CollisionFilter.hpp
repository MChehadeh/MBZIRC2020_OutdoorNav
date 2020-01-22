#pragma once
#include "MsgEmitter.hpp"
#include "MsgReceiver.hpp"
#include "Vector3D.hpp"
#include "Vector3DMessage.hpp"
#include "filterPointMsg.hpp"
#include <vector>       // For std::vector
#include <algorithm>    // For std::sort
#include <cmath>
class CollisionFilter : public msg_receiver, public msg_emitter {

private:
    std::vector<float> x_hitpoint;
    std::vector<float> y_hitpoint;
    std::vector<float> z_hitpoint;
    void receive_msg_data(DataMessage* t_msg);
    void FilteringHitPoint(Vector3D<float>);
    void getAvg(Vector3D<float>);
    Vector3D<float> avg;
    Vector3D<float> median;
    int counter = 0;
    const int median_filter_window_size = 5;
    const int median_index = std::floor(median_filter_window_size/2.);
    const int confidence_num_of_averaged_samples = 10;
    building_sides side_filter;
public:
    CollisionFilter();
    ~CollisionFilter();
};