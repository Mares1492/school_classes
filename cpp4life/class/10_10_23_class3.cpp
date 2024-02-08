#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector> // Include the vector header

struct Point {
    int x = 0;
    int y = 0;
    int z = 0;
};

double calc_distance(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}


int main() {
    Point ant, ant_goal;
    int cuboid_x, cuboid_y, cuboid_z;
    std::cin >> ant.x >> ant.y >> ant.z;
    std::cin >> cuboid_x >> cuboid_y >> cuboid_z;
    std::cin >> ant_goal.x >> ant_goal.y >> ant_goal.z;

   

    return 0;
}
