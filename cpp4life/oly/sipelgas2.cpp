#include <iostream>
#include <cmath>
#include <vector>

bool checkIsSameFace(int value1,int value2,int max){
    return ((value1 == 0 || value1 == max) && value1 == value2);
}

bool checkIsOppositeFace(int value1,int value2,int max){
    return ((value1 == 0 && value2 == max) || (value1 == max && value2 == 0));
}

int main() {
    int Xr, Yr, Zr, Xs, Ys, Zs, Xm, Ym, Zm;
    
    // Input
    std::cin >> Xr >> Yr >> Zr;
    std::cin >> Xs >> Ys >> Zs;
    std::cin >> Xm >> Ym >> Zm;

   
    int dx = abs(Xs - Xm);
    int dy = abs(Ys - Ym);
    int dz = abs(Zs - Zm);

    double shortest_path;
    std::vector<double>unfoldings(5);

    if (checkIsSameFace(Xs,Xm,Xr)||checkIsSameFace(Ys,Ym,Yr)||checkIsSameFace(Zs,Zm,Zr))
    {
        unfoldings.resize(1);
        unfoldings[0] = dx + dy + dz;
    }
    
    else if (checkIsOppositeFace(Xs,Xm,Xr) || checkIsOppositeFace(Ys,Ym,Yr) || checkIsOppositeFace(Zs,Zm,Zr))
    {
        int a1 = Zr+dy, b1 = dx;
        int a2 = Zr + dy, b2 = (Xr-Xm)+Ym;
        int a3 = Zr + dy , b3 = (Xr-Xm)+Yr+((Xr-Xm));
        int a4 = Zr + dy, b4 = Xm + Ym;
        int a5 = Zr + dy, b5 = Xm + Xr + Xm;
        unfoldings[0] = sqrt((a1*a1) + (b1*b1));
        unfoldings[1] = sqrt((a2*a2) + (b2*b2));
        unfoldings[2] = sqrt((a3*a3) + (b3*b3));
        unfoldings[3] = sqrt((a4*a4) + (b4*b4));
        unfoldings[4] = sqrt((a5*a5) + (b5*b5));
    }
    else
    {
        unfoldings.resize(3);
        int a1 = dx+dy, b1 = dz;
        int a2 = Zs + dy, b2 = Zm + dx;
        int a3 = (Zr-Zs) + dy, b3 = (Zr-Zm)+dx;
        unfoldings[0] = sqrt((a1*a1) + (b1*b1));
        unfoldings[1] = sqrt((a2*a2) + (b2*b2)); // Through a bordering face
        unfoldings[2] = sqrt((a3*a3) + (b3*b3)); // Through another bordering face 
    }

    //std::cout << unfoldings[0] << '\n'<< unfoldings[1] << '\n'<< unfoldings[2] << "\n\n";

    shortest_path = unfoldings[0];

    for (size_t i = 1; i < unfoldings.size(); i++)
    {
        shortest_path = std::min(shortest_path,unfoldings[i]);
    }
    

    // Output the result
    //std::cout <<  "Shortest path: " <<shortest_path;
    std::cout << shortest_path;

    return 0;
}
