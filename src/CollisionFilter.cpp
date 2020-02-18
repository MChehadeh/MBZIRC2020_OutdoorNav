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
    //std::cout << "Hit Point: " << t_hitPoint.x << ", " << t_hitPoint.y << ", " << t_hitPoint.z << std::endl;
    if(x_hitpoint.size() < median_filter_window_size) 
    {
        x_hitpoint.push_back(t_hitPoint.x);
        y_hitpoint.push_back(t_hitPoint.y);
        z_hitpoint.push_back(t_hitPoint.z);
    }
    if (x_hitpoint.size() == median_filter_window_size)  
    {
        std::sort(x_hitpoint.begin(), x_hitpoint.end());
        std::sort(y_hitpoint.begin(), y_hitpoint.end());
        std::sort(z_hitpoint.begin(), z_hitpoint.end());
        
        median.x = x_hitpoint.at(median_index);
        median.y = y_hitpoint.at(median_index);
        median.z = z_hitpoint.at(median_index);
        getAvg(median);
        std::cout << "Median Point: " << median.x << ", " << median.y << ", " << median.z << std::endl;
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
    if (counter == 0){
        avg = t_avg;
    }
    else if (counter > 0){
        avg = avg*((float)counter/((float)counter+1.)) + (t_avg/((float)counter+1.));
        std::cout << "Accum Average Point: " << avg.x << ", " << avg.y << ", " << avg.z << std::endl;
    }
    counter++;
    if (counter == confidence_num_of_averaged_samples)
    {
        filterPointMsg filteredFirePoint;
        filteredFirePoint.setFilterMessage(avg);
        filteredFirePoint.side_of_hit = this->side_filter;
        std::cout << "Final Average Point: " << avg.x << ", " << avg.y << ", " << avg.z << std::endl;
        std::cout << "Final Side of Hit: " << (int)filteredFirePoint.side_of_hit << std::endl;
        this->emit_message((DataMessage*) &filteredFirePoint);
    }

}