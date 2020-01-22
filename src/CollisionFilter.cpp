#include "CollisionFilter.hpp"

CollisionFilter::CollisionFilter() {
}
CollisionFilter::~CollisionFilter() {
}

void CollisionFilter::receive_msg_data(DataMessage* t_msg)
{
    if (t_msg->getType() == msg_type::FILTER_POINT) {
        filterPointMsg* tmp = ((filterPointMsg*) t_msg);
        if (tmp->side_of_hit==side_filter){
            FilteringHitPoint(tmp->filterPoint);
        }
    }
}

void CollisionFilter::FilteringHitPoint(Vector3D<float> t_hitPoint)
{
    if(x_hitpoint.size() < median_filter_window_size) 
    {
        x_hitpoint.push_back(t_hitPoint.x);
        y_hitpoint.push_back(t_hitPoint.y);
        z_hitpoint.push_back(t_hitPoint.z);
    }
    else if (x_hitpoint.size() == median_filter_window_size)  
    {
        x_hitpoint.push_back(t_hitPoint.x);
        y_hitpoint.push_back(t_hitPoint.y);
        z_hitpoint.push_back(t_hitPoint.z);
        std::sort(x_hitpoint.begin(), x_hitpoint.end());
        std::sort(y_hitpoint.begin(), y_hitpoint.end());
        std::sort(z_hitpoint.begin(), z_hitpoint.end());
        
        median.x = x_hitpoint.at(median_index);
        median.y = y_hitpoint.at(median_index);
        median.z = z_hitpoint.at(median_index);
        getAvg(median);
        x_hitpoint.clear();
        y_hitpoint.clear();
        z_hitpoint.clear();
    }
}

void CollisionFilter::getAvg(Vector3D<float> t_avg)
{
    if (counter > confidence_num_of_averaged_samples){
        return;
    }
    if (counter == confidence_num_of_averaged_samples)
    {
        filterPointMsg filteredFirePoint;
        filteredFirePoint.setFilterMessage(avg);
        filteredFirePoint.side_of_hit = this->side_filter;
        this->emit_message((DataMessage*) &filteredFirePoint);
    }
    if (counter == 0){
        avg = t_avg;
    }
    else if (counter > 0){
        avg = avg*(counter/(counter+1)) + (t_avg/(counter+1));
    }
    counter++;
}