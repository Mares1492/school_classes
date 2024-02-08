#include <iostream>
#include <cstdlib>
#include <ctime>
//Game about two players trying to finish the last in the race
int p1_pos = -1,p2_pos = -1, winner = 0,currentP = 1, line[7],mode;

int get_random_step(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Generate a random integer 1 or 2
    return (std::rand() % 2) + 1;
}

int is_pos_free(int pos){
    return line[pos] != 1 && line[pos] != 2;
}

int handle_p_turn(int p_pos){
    int steps = 0;
    line[p_pos] = 0;
    while (steps == 0)
    {
        std::cout << "Enter steps: ";
        std::cin >> steps;
        if (!is_pos_free(p_pos + steps))
        {
            steps = 0;
            std::cout << "Cell is taken. Try again.\n";
        }
        if (steps != 1 && steps != 2){
            steps = 0;
            std::cout << "Enter valid steps value(1 or 2).\n";
        }
        
    } 

    std:: cout << "\n";
    line[p_pos+steps] = currentP;
    return p_pos + steps;
}

int handle_e_turn(int p_pos){
    line[p_pos] = 0;
    if (is_pos_free(p_pos + 1))
    {
        line[p_pos+1] = currentP;
        return p_pos + 1;
    }
    line[p_pos+2] = currentP;
    return p_pos + 2;
}

void round(){
    if (mode == 1){
        if (currentP == 1){
            std::cout << "Players turn\n";
            p1_pos = handle_p_turn(p1_pos);
        }else{
            std::cout << "ENV turn\n";
            p2_pos = handle_e_turn(p2_pos);
        }
    }
    if (mode == 2){
        if (currentP == 1){
            p1_pos = handle_e_turn(p1_pos);
        }else{
            p2_pos = handle_e_turn(p2_pos);
        }
    }
    if (mode == 3){
        std::cout << "Player " << currentP << " turn\n";
        std::cout << "Enter steps: ";
        if (currentP == 1){
            p1_pos = handle_p_turn(p1_pos);
        }else{
            p2_pos = handle_p_turn(p2_pos);
        }
    }
}

void print_line(){
    for (int i = 0; i < 7; i++) {
        std::cout << "[" << line[i] << "]";
    }
    std::cout << "\n";
}

int main(){
    int cicle = 0;
    std::cout << "Modes: 1)PvE 2)EvE 3)PvP\nSelect mode: ";

    while (mode < 1 || mode > 3){
        std::cin >> mode;
    }
    while (line[6]==0)
    {
        round();
        print_line();
        if (currentP == 1)
        {
            currentP = 2;
        }else{
            currentP = 1;
        }
        cicle++;
        if ( cicle > 100){
            std::cerr << "inf loop";
            return 1;
        }

    }
    if (line[6] == 1){
        winner = 2;
    }else{
        winner = 1;
    }
    std::cout << "The winner is: Player "<< winner <<"\n";
    return 0;
    
}



