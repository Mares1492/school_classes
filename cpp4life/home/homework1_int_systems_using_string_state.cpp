#include <iostream>
#include <ctime>
#include <stdlib.h> 
#include <vector>
#include <algorithm>
#include <map>


std::string board = "123456789"; // mängulaud
std::vector<int> cells = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // vabad kohad
std::map <int,int> win_chances;
char player = 'X';
char env = 'O';

void erase_cell(int cell_value){
    auto cell_index = std::find(cells.begin(), cells.end(), cell_value);
    if (cell_index != cells.end()) {
        cells.erase(cell_index);
    }
}

int get_random_cell(const std::vector<int>& cells_to_choose_from){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int cellIndex = std::rand() % cells_to_choose_from.size();
    return cells_to_choose_from[cellIndex];
}

int is_pos_free(char held_by){
    return held_by != 'X' && held_by != 'O'; 
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
        if (is_pos_free(board[cell_to_take-1]))
        {
            board[cell_to_take-1] = player;
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
        cell_to_take = get_random_cell(cells);
        if (is_pos_free(board[cell_to_take-1])){
            board[cell_to_take-1] = env;
            erase_cell(cell_to_take);
        }
        else{
            cell_to_take = 0;
        }
    }
    std::cout << "ENV: " << cell_to_take << "\n";
}

char check_win(const std::string& game_state, char side) { //game_state on mängulaud mida ei saa muuta
    const std::string win_combinations[] = 
    {
        "123",
        "456", 
        "789", 
        "147", 
        "258", 
        "369", 
        "159", 
        "357"
    };

    for (const std::string& combination : win_combinations) {
        bool won = true;
        for (char index : combination) {
            if (game_state[index - '1'] != side) {
                won = false;
                break;
            }
        }
        if (won) {
            return side;
        }
    }
    return '-';
}

void print_cells(){
    std::cout << "Free cells: ";
    for (auto&& cell : cells)
    {
        std::cout << "[" << cell << "]";
    }
    std::cout << "\n";
}

void print_board(const std::string& board_to_print,bool is_print_cells = true,int size_of_indent=0){
    if (is_print_cells)
    {
        print_cells();
        std::cout << "Current state: \n";
    }
    std::cout << "---";
    for(std::size_t i = 0;i<board_to_print.size();i++){
        if (i % 3 == 0){
            std::cout << '\n';
            std::cout << std::string(size_of_indent*2, ' ');
        }
        std::cout << "[" << board_to_print[i] << "]";
    }
    std::cout << "\n"<<"---" << "\n";
}

void handle_side_pick(){
    char side_to_pick = '-';
    while (side_to_pick == '-')
    {
        std::cout << "Pick side(X or O): ";
        std::cin >> side_to_pick;
        side_to_pick = toupper(side_to_pick);
        if (side_to_pick != 'X' && side_to_pick != 'O')
        {
            system("cls");
            side_to_pick = '-';
        }
    }
    if (side_to_pick == 'X')
    {
        player = 'X';
        env = 'O';
        return;
    }
    player = 'O';
    env = 'X';
}

int calc_prob_steps(std::string new_board,int eter,char who){
    std::vector<int> free_cells;
    char who_next;
    int wins = 0;
    if (eter==1)
    {
        print_board(new_board,false,eter);
    }
    
    if (check_win(new_board, player)==player)
    {
        if (eter==1)
        {
            std::cout<<"Win power : Absolute\n---\nNEXT\n";
        }
        return wins + 1;
    }
    if (check_win(new_board, env)==env)
    {
        if (eter==1)
        {
            std::cout<<"Win power : None\n"<<"---\nNEXT\n";
        }
        return wins - 1;
    }
    for (size_t i = 0; i < new_board.size(); i++)
    {
        if(new_board[i] >= '0' && new_board[i] <= '9'){
            free_cells.push_back(i);
        }
    }
    if (free_cells.size())
    {
        
        for (auto &&i : free_cells)
        {
            std::string next_board = new_board;
            next_board[i] = who;
            if (eter == 0)
            {
                std::cout<< "If "<< who << " is set to ["<<i+1<<"]\n";

            }
            if (who == 'X')
            {
                who_next = 'O';
            }
            else
            {
                who_next = 'X';
            }
            wins += calc_prob_steps(next_board,eter+1,who_next);
        }
        if (eter == 1)
        {
            std::cout<<"Win power :"<<wins<<'\n'<<"---\nNEXT\n";
            //win_chances[];
        }
    }
    return wins;
}

int main() {
    system("cls");
    handle_side_pick();
    bool is_players_turn = (player == 'X');
    
    char winner = '-';
    while (winner == '-')
    {
        if (!cells.size())
        {
            break;
        }
        if (is_players_turn)
        {   
            if (cells.size() != 9)
            {
                int wins = calc_prob_steps(board,0,player);
                std::cout << "Sum of win power: " << wins <<"\n\n";
            }
            print_board(board);
            handle_p_turn();
            winner =  check_win(board, player);
        }
        else
        {
            handle_e_turn();
            winner = check_win(board, env);
        }
        is_players_turn = !is_players_turn;
        
    }
    print_board(board);
    if (winner == player) {
        std::cout << "Player wins!";
    } 
    if (winner == env) {
        std::cout << "ENV wins...";
    }
    if (winner == '-') {
        std::cout << "DEAD HEAT";
    }

    return 0;
}
