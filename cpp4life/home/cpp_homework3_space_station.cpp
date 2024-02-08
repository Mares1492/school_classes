//Õhuleke kosmosejaamas
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <set>
#include <chrono>

// Täitmisaeg(käitusaeg): 12-25 millisekundit
// Failinimed konstantidena
const std::string input_file_path = "../input/station_input.txt";
const std::string output_file_path = "station_output.txt";

struct Module
{
    int x,y,z;
    std::list<std::string> directions;
};

std::ifstream input_file;
std::ofstream output_file;
std::map<std::string, Module> modules;

// võrdlusfunktsioon moodulite sortimiseks
bool compare_modules(const Module& module1, const Module& module2) {
    std::string key1 = std::to_string(module1.z) + std::to_string(module1.y) + std::to_string(module1.x);
    std::string key2 = std::to_string(module2.z) + std::to_string(module2.y) + std::to_string(module2.x);
    
    return key1 < key2; // Sorteerib xyz võtme alusel
}

std::set<Module, decltype(compare_modules)*> leak_modules(compare_modules);

// Funktsioon avab sisendfaili ja kontrollib et oleks avatud
bool open_input_file(std::ifstream& input_file) {
    input_file.open(input_file_path);
    return input_file.is_open();
}

// Funktsioon avab väljundfaili ja kontrollib
bool open_output_file(std::ofstream& output_file) {
    output_file.open(output_file_path);
    return output_file.is_open();
}

std::string load_blocks_data(){
    int U;
    input_file >> U;// uksete number nt 5
    for (int i = 0; i < U+1; i++) {
        int x,y,z;
        std::string room,direction;
        input_file >> x >> y >> z;
        room=std::to_string(x)+std::to_string(y)+std::to_string(z);
        if (i<U)
        {
            input_file >> direction;
            std::cout << "Open doors: [Room: " << room << ", Direction: " << direction << "]\n";
            modules[room].x = x;modules[room].y = y;modules[room].z = z;
            modules[room].directions.push_back(direction);
        }
        else
        {
            std::cout << "Broken module is found: " << room << "\nScanning path...\n";
            return room;
        }
    }
    return "111";
}

void check_leaks(std::string current_module){
    std::cout << "\nCurrent module: " << current_module << '\n';
    std::cout << "Number of open doors: " << modules[current_module].directions.size() << '\n';
    leak_modules.insert(modules[current_module]);
    if (modules[current_module].directions.empty())
    {
        std::cout << "Dead end! Returning...\n";
        return;
    }
    
    while (!modules[current_module].directions.empty()) 
    {
        int x = modules[current_module].x,y=modules[current_module].y,z=modules[current_module].z;
        std::string direction = modules[current_module].directions.front(); 
        modules[current_module].directions.pop_front(); 
        bool is_sum = direction[1] == '+';
        std::cout << direction;
        switch (direction[0])
        {
        case 'X':
            if (is_sum)
            {
                x++;
            }
            else
            {
                x--;
            }
            break;
        case 'Y':
            if (is_sum)
            {
                y++;
            }
            else
            {
                y--;
            }
            break;
        case 'Z':
            if (is_sum)
            {
                z++;
            }
            else
            {
                z--;
            }
            break;
        }
        std::cout << "\nNEXT\n";
        std::string new_module = std::to_string(x)+std::to_string(y)+std::to_string(z);     
        check_leaks(new_module);
    }
    
}

int main(){
    auto start_time = std::chrono::high_resolution_clock::now();
    
    if (!open_input_file(input_file)) {
        std::cerr << "Error opening input file: " << input_file_path << "\n";
        return 1;
    }

    // Kontrollime, kas valjundfaili avamine õnnestus, ja loome uue, kui vajalik
    if (!open_output_file(output_file)) {
        std::cout << "Output file not found." << "\n";
        return 1;
    }

    /*
        - loeme bloki andmed failist
        - leiame katkise bloki
        - kontrollime blokid avatud ustega
    */
    check_leaks(load_blocks_data());

    std::cout << "\nListing leak modules: \n";
    for (auto &&module : leak_modules)
    {   
        if (module.x != 0 && module.y != 0 && module.z != 0)
        {
            output_file << module.x << " " << module.y << " " << module.z<<'\n';
            std::cout << module.x << " " << module.y << " " << module.z<<'\n';

        }  
    }
    input_file.close();
    output_file.close();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
    
}
