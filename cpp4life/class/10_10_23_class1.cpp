#include <iostream>

int main(){
    long double
    heat_energy_drain_per_grade,
    grade_scale_per_second,
    heat_save_energy_drain_per_minute,
    water_normal_cool_down_per_minute;

    std::cin 
    >> heat_energy_drain_per_grade
    >> grade_scale_per_second
    >> heat_save_energy_drain_per_minute
    >> water_normal_cool_down_per_minute;

    std::cout << heat_save_energy_drain_per_minute*60.0<<'\n';
    long double 
        temp = 100,
        time = 3600000,
        grades_per_one_second = (1/grade_scale_per_second) / 1000,
        water_cool_down_tic = (water_normal_cool_down_per_minute/60) / 1000;

    while (temp + (time*grades_per_one_second)>100.0L && temp > 22.0L)
    {
        temp -= water_cool_down_tic;
        time -= 1.0L;
    }
    
    //std::cout << "Temperature|Time " << temp << '|' << (3600000 - time)/1000/60 <<'\n';
    std::cout <<  heat_energy_drain_per_grade * (100.0L-temp);
    return 0;
}