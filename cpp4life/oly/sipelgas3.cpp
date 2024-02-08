#include <iostream>
#include <cmath>
#include <vector>

int main() {
    int Xr, Yr, Zr, Xs, Ys, Zs, Xm, Ym, Zm;
    
    // Input
    std::cin >> Xr >> Yr >> Zr;
    std::cin >> Xs >> Ys >> Zs;
    std::cin >> Xm >> Ym >> Zm;

   
    int dx = abs(Xs - Xm);
    int dy = abs(Ys - Ym);
    int dz = abs(Zs - Zm);

    // Output the result
    //std::cout <<  "Shortest path: " <<shortest_path;
    std::cout << dx + dy + dz;;

    return 0;
}