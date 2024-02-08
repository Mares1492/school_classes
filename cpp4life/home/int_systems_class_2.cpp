#include <iostream>
#include <list>
#include <fstream>

/*
2 -> K(vaipade arv) 8 -> L(Area.x) 9 -> P(area.y)
3 3 3 0 -> N,E,S,W


*/

struct FieldArea {
    int x = 0;
    int y = 0;
    int field_data[0][0];
};

struct Carpet {
    int nr,north, south, east, west;
};

FieldArea area;
std::list<Carpet> carpets;

int main(){
    std::cout<< "Enter field area.\nX:";
    std::cin >> area.x;
    std::cout << "Y:";
    std::cin >> area.y;
    std::cout << "\n";
    return 0;
}

void printField(){
    for(int i= 0; i< area.x+area.y;i++){
        std::cout << "[" << area.field_data[i] << "]";
    }
}
