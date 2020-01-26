#include "print_utility.hpp"
using namespace std;

void print_utility::print_vec_3d(vector<Vector3D<double>> lst_vec){
    cout<< "================ Begin Vec3D Print ===================\n"; 
    for (int i=0; i< lst_vec.size();i++){
        cout<< "Vector3D: " <<lst_vec[i].x <<", " <<lst_vec[i].y<< ", " <<lst_vec[i].z<<"\n";
    }
    cout<< "Total Size: " <<lst_vec.size() <<"\n";
    cout<< "================= End Vec3D Print ====================\n"; 
}

void print_utility::print_vec_3d(Vector3D<double> lst_vec){
    //cout<< "================ Begin Vec3D Print ===================\n"; 
    
    cout<< "Vector3D: " <<lst_vec.x <<", " <<lst_vec.y<< ", " <<lst_vec.z<<"\n";
    
    //cout<< "================= End Vec3D Print ====================\n"; 
}

void print_utility::print_vec_2d(vector<Vector2D<double>> lst_vec){
    cout<< "================ Begin Vec3D Print ===================\n"; 
    for (int i=0; i< lst_vec.size();i++){
        cout<< "Vector2D: " <<lst_vec[i].x <<", " <<lst_vec[i].y<< "\n";
    }
    cout<< "Total Size: " <<lst_vec.size() <<"\n";
    cout<< "================= End Vec3D Print ====================\n"; 
}

void print_utility::print_vec_2d(Vector2D<double> lst_vec){
    //cout<< "================ Begin Vec3D Print ===================\n"; 
    
    cout<< "Vector2D: " <<lst_vec.x <<", " <<lst_vec.y<< "\n";
    
    //cout<< "================= End Vec3D Print ====================\n"; 
}

void print_utility::print_vec_rect(vector<Rectangle> lst_rect){
    cout<< "================ Begin Rect Print ===================\n"; 
    for (int i=0; i< lst_rect.size();i++){
        cout<< "Side1: (" <<lst_rect[i].getSide1().getPoint1().x <<"," <<lst_rect[i].getSide1().getPoint1().y<< "), ("
         <<lst_rect[i].getSide1().getPoint2().x <<"," <<lst_rect[i].getSide1().getPoint2().y<<")\n";
        cout<< "Side2: (" <<lst_rect[i].getSide2().getPoint1().x <<"," <<lst_rect[i].getSide2().getPoint1().y<< "), ("
         <<lst_rect[i].getSide2().getPoint2().x <<"," <<lst_rect[i].getSide2().getPoint2().y<<")\n";
        cout<< "Center: (" <<lst_rect[i].getCenter().x <<"," <<lst_rect[i].getCenter().y<< ")\n";
    }
    cout<< "Total Size: " <<lst_rect.size() <<"\n";
    cout<< "================= End Rect Print ====================\n"; 
}

void print_utility::print_vec_rect(Rectangle lst_rect){
    cout<< "================ Begin Rect Print ===================\n"; 
    
        cout<< "Side1: (" <<lst_rect.getSide1().getPoint1().x <<"," <<lst_rect.getSide1().getPoint1().y<< "), ("
         <<lst_rect.getSide1().getPoint2().x <<"," <<lst_rect.getSide1().getPoint2().y<<")\n";
        cout<< "Side2: (" <<lst_rect.getSide2().getPoint1().x <<"," <<lst_rect.getSide2().getPoint1().y<< "), ("
         <<lst_rect.getSide2().getPoint2().x <<"," <<lst_rect.getSide2().getPoint2().y<<")\n";
        cout<< "Center: (" <<lst_rect.getCenter().x <<"," <<lst_rect.getCenter().y<< ")\n";
    
    cout<< "================= End Rect Print ====================\n"; 
}

void print_utility::print_vec_line(vector<Line2D> lst_line){
    cout<< "================ Begin Line Print ===================\n"; 
    for (int i=0; i< lst_line.size();i++){
        cout<< "P1: (" <<lst_line[i].getPoint1().x <<"," <<lst_line[i].getPoint1().y<< "), P2: ("
         <<lst_line[i].getPoint2().x <<"," <<lst_line[i].getPoint2().y<<"), Length: "<< lst_line[i].getLength()  << "\n";
    }
    cout<< "Total Size: " <<lst_line.size() <<"\n";
    cout<< "================= End Line Print ====================\n"; 
}

void print_utility::print_vec_line(Line2D lst_line){
    cout<< "================ Begin Line Print ===================\n"; 
    cout<< "P1: (" <<lst_line.getPoint1().x <<"," <<lst_line.getPoint1().y<< "), P2: ("
         <<lst_line.getPoint2().x <<"," <<lst_line.getPoint2().y<<"), Length: "<< lst_line.getLength()<< "\n";
    cout<< "================= End Line Print ====================\n"; 
}

void print_utility::print_waypoint(vector<Waypoint> lst_wp){
    cout<< "================ Begin Waypoint Print ===================\n"; 
    for (int i=0; i< lst_wp.size();i++){
        print_waypoint(lst_wp[i]);
    }
    cout<< "Total Size: " <<lst_wp.size() <<"\n";
    cout<< "================= End Waypoint Print ====================\n"; 
}

void print_utility::print_waypoint(Waypoint wp){
    print_vec_3d(wp.position);
    cout<< "Yaw: " <<wp.yaw <<"\n";
}