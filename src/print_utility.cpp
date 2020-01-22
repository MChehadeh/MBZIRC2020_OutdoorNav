#include "print_utility.hpp"
void print_vec_3d(vector<Vector3D<double>> lst_vec){
    cout<< "================ Begin Vec3D Print ===================\n"; 
    for (int i=0; i< lst_vec.size();i++){
        cout<< "waypoint: " <<lst_vec[i].x <<", " <<lst_vec[i].y<< ", " <<lst_vec[i].z<<"\n";
    }
    cout<< "================= End Vec3D Print ====================\n"; 
}

void print_vec_3d(Vector3D<double> lst_vec){
    cout<< "================ Begin Vec3D Print ===================\n"; 
    
    cout<< "waypoint: " <<lst_vec.x <<", " <<lst_vec.y<< ", " <<lst_vec.z<<"\n";
    
    cout<< "================= End Vec3D Print ====================\n"; 
}

void print_vec_rect(vector<Rectangle> lst_rect){
    cout<< "================ Begin Rect Print ===================\n"; 
    for (int i=0; i< lst_rect.size();i++){
        cout<< "Side1: (" <<lst_rect[i].getSide1().getPoint1().x <<"," <<lst_rect[i].getSide1().getPoint1().y<< "), ("
         <<lst_rect[i].getSide1().getPoint2().x <<"," <<lst_rect[i].getSide1().getPoint2().y<<")\n";
        cout<< "Side2: (" <<lst_rect[i].getSide2().getPoint1().x <<"," <<lst_rect[i].getSide2().getPoint1().y<< "), ("
         <<lst_rect[i].getSide2().getPoint2().x <<"," <<lst_rect[i].getSide2().getPoint2().y<<")\n";
        cout<< "Center: (" <<lst_rect[i].getCenter().x <<"," <<lst_rect[i].getCenter().y<< ")\n";
    }
    cout<< "================= End Rect Print ====================\n"; 
}

void print_vec_rect(Rectangle lst_rect){
    cout<< "================ Begin Rect Print ===================\n"; 
    
        cout<< "Side1: (" <<lst_rect.getSide1().getPoint1().x <<"," <<lst_rect.getSide1().getPoint1().y<< "), ("
         <<lst_rect.getSide1().getPoint2().x <<"," <<lst_rect.getSide1().getPoint2().y<<")\n";
        cout<< "Side2: (" <<lst_rect.getSide2().getPoint1().x <<"," <<lst_rect.getSide2().getPoint1().y<< "), ("
         <<lst_rect.getSide2().getPoint2().x <<"," <<lst_rect.getSide2().getPoint2().y<<")\n";
        cout<< "Center: (" <<lst_rect.getCenter().x <<"," <<lst_rect.getCenter().y<< ")\n";
    
    cout<< "================= End Rect Print ====================\n"; 
}

void print_vec_line(vector<Line2D> lst_line){
    cout<< "================ Begin Line Print ===================\n"; 
    for (int i=0; i< lst_line.size();i++){
        cout<< "P1: (" <<lst_line[i].getPoint1().x <<"," <<lst_line[i].getPoint1().y<< "), P2: ("
         <<lst_line[i].getPoint2().x <<"," <<lst_line[i].getPoint2().y<<"), Length: "<< lst_line[i].getLength()  << "\n";
    }
    cout<< "================= End Line Print ====================\n"; 
}

void print_vec_line(Line2D lst_line){
    cout<< "================ Begin Line Print ===================\n"; 
    cout<< "P1: (" <<lst_line.getPoint1().x <<"," <<lst_line.getPoint1().y<< "), P2: ("
         <<lst_line.getPoint2().x <<"," <<lst_line.getPoint2().y<<"), Length: "<< lst_line.getLength()<< "\n";
    cout<< "================= End Line Print ====================\n"; 
}