#include <iostream> 
#include <ctime>
#include <stdlib.h> 
#include <vector>
#include <algorithm>


const int SIZE = 3;

char winner = '-';

struct Cell {
    std::string heldBy = " ";
};

std::string field[SIZE][SIZE];
std::vector<int> cells = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void erase_cell(int cell_value){
    auto cell_index = std::find(cells.begin(), cells.end(), cell_value);

    if (cell_index != cells.end()) {
        cells.erase(cell_index);
    }
}

int get_random_cell(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int cellIndex = std::rand() % cells.size();
    return cells[cellIndex];
}

int is_pos_free(std::string heldBy){
    return heldBy != "X" && heldBy != "O"; 
}

void handle_p_turn(){
    int cell_to_take = 0;
    while (cell_to_take == 0)
    {
        std::cout << "Enter free cell nr (from 1 to 9): ";
        std::cin >> cell_to_take;
        if (cell_to_take < 1 || cell_to_take > 9){
            
            cell_to_take = 0;
            continue;
        }
        int x = (cell_to_take - 1) / SIZE;
        int y = (cell_to_take - 1) % SIZE;
        if (is_pos_free(field[y][x]))
        {
            field[y][x] = "X";
            erase_cell(cell_to_take);
            system("cls");
        }
        else
        {
            cell_to_take = 0;
            std::cout << "Cell is taken. Try again.\n";
        }
    } 
    
}

void handle_e_turn(){
    int cell_to_take = 0;
    while (cell_to_take == 0)
    {
        cell_to_take = get_random_cell();
        int x = (cell_to_take - 1) / SIZE;
        int y = (cell_to_take - 1) % SIZE;
        if (is_pos_free(field[y][x])){
            field[y][x] = "O";
            erase_cell(cell_to_take);
        }
        else{
            cell_to_take = 0;
        }
    }
    std::cout << "ENV: " << cell_to_take << "\n";
}

void print_cells(){
    std::cout << "Free cells: ";
    for (auto &&cell : cells)
    {
        std::cout << "[" << cell << "]";
    }
    std::cout << "\n";
}

void check_field(){
    print_cells();
    std::cout << "---" << "\n";
    for (int x = 0;x<SIZE;x++){
        for (int y = 0;y<SIZE;y++){
            std::cout << "[" << field[y][x] <<"]";
        }
        std::cout << "\n";
    }
    std::cout << "---" << "\n";
}

int main()
{
    bool is_players_turn = true;
    system("cls");
    std::cout << "\n" << "---" << "\n";
    int counter = 0;
    for (int x = 0;x<SIZE;x++){
        for (int y = 0;y<SIZE;y++){
            field[y][x] = std::to_string(++counter);
            std::cout << "[" << field[y][x] <<"]";
        }
        std::cout << "\n";
    }
    std::cout << "---" << "\n\n";
    while (winner == 0)
    {
        if (is_players_turn)
        {
            handle_p_turn();
        }
        else
        {
            handle_e_turn();
        }
        is_players_turn = !is_players_turn;
        check_field();
        
    }
    system("cls");
    check_field();
    return 0;
}


