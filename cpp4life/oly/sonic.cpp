#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <memory>

const char BLUE = 'o';
const char EMPTY = '.';
const char WHITE = '#';
const char RED = 'x';
const char SONIC = 'S';

struct Position {
    int row = 0,column = 0;
};

struct Cell {
    char symbol = '.';
    bool in_cluster = false;
    int cluster_id = 0;
    Position position;
};

struct Cluster
{
    std::vector<Cell> elements;
    Position middle_point;
    bool is_marked_for_deletion = false;
};

struct Sonic
{
    Position current_position;
    std::unique_ptr<Cluster> target;

    Sonic() : current_position({0, 0}), target(nullptr) {}
    // Constructor to set the initial target
    Sonic(Position pos) : current_position(pos), target(nullptr) {}

    // Function to change the target
    void setTarget(std::unique_ptr<Cluster> new_target) {
        target = std::move(new_target);
    }

};


// Failinimed konstantidena
const std::string input_file_path = "../input/sonic.txt";
const std::string output_file_path = "sonic_output.txt";

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

bool has_neighboring_cluster(Cell& last_cell_in_prev_cluster,Cell& cell){
    //std::cout << '\n' <<cell.position.column << " | " << last_cell_in_prev_cluster.position.column+1<<'\n';
    return cell.position.column == last_cell_in_prev_cluster.position.column+1;
}

bool can_clusters_pair(Cluster cluster_to_pair,Cluster cluster_to_check){
    int cluster_to_pair_last_row = cluster_to_pair.elements.back().position.row;
    int cluster_to_check_last_row = cluster_to_check.elements.back().position.row;
    if (cluster_to_pair_last_row + 1 == cluster_to_check_last_row){
        int cluster_to_check_first_el_pos = cluster_to_check.elements.front().position.column;
        int cluster_to_check_last_el_pos = cluster_to_check.elements.back().position.column;
        int cluster_to_pair_first_el_pos = cluster_to_pair.elements.front().position.column;
        int cluster_to_pair_last_el_pos = cluster_to_pair.elements.back().position.column;
        if (
            cluster_to_pair_last_el_pos < cluster_to_check_first_el_pos-1 || 
            cluster_to_check_last_el_pos <  cluster_to_pair_first_el_pos-1
            )
        {
            return false;
        }
        return true;
        
    }
    return false;
}

void set_target(Sonic& sonic,Cluster &target_cluster){
    std::unique_ptr<Cluster> clusterPtr = std::make_unique<Cluster>(target_cluster);
    sonic.setTarget(std::move(clusterPtr));
}

bool get_shortest_path_to_Cell
    (
        Position current,
        const Position& target,
        const char next_move,
        const std::vector<Cluster> &blue_clusters,
        std::vector<char> &path
    )
    {
    switch (next_move)
    {
    case 'U':
        current.column++;
        break;
    
    case 'R':
        current.row++;
        break;

    case 'D':
        current.column--;
        break;

    case 'L':
        current.row--;
        break;
    }
    if 
    (
        blue_clusters[current.row].elements[current.column].symbol == RED 
        ||
        blue_clusters[current.row].elements[current.column].symbol == WHITE
    )
    {
        return false;
    }
    path.push_back(next_move);

    if (current.column == target.column && current.row == target.row)
    {
        return true;
    }

    std::vector<char> moves = {'U','R','D','L'};

    if (!path.empty()) {
        char lastPathElement = path.back();
        
        for (auto it = moves.rbegin(); it != moves.rend(); ++it) 
        {
            if (*it == lastPathElement) {
                // Remove the matching element from moves
                moves.erase(std::next(it).base()); 
                break;
            }
        }
    }
    
    for (auto &&move : moves)
    {
        get_shortest_path_to_Cell(current,target,move,blue_clusters,path);
    }
    //return path
}

int main() {
    std::ifstream input_file;
    std::ofstream output_file;

    if (!open_input_file(input_file)) {
        std::cerr << "Error opening input file: " << input_file_path << "\n";
        return 1;
    }

    if (!open_output_file(output_file)) {
        std::cout << "Output file not found. Creating a new one: " << output_file_path << "\n";
        output_file.open(output_file_path);
    }

    int ROW, COL;
    if (!(input_file >> ROW >> COL) || ROW <= 0 || COL <= 0) {
        std::cerr << "Invalid or missing N or K values in input file.\n";
        return 1;
    }

    std::vector<std::vector<Cell>> field(ROW, std::vector<Cell>(COL));
    std::vector<Cluster> blue_clusters;

    Sonic sonic;

    std::cout << "\n\nPrinting map: \n\n";
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            char sym;
            input_file >> sym;
            Cell cell; 
            cell.symbol = sym;
            cell.position.row = row;cell.position.column = col;
            field[row][col] = cell;
            if (sym == SONIC)
            {
                sonic.current_position.row = row;
                sonic.current_position.column = col;
            }
            
            if (sym == BLUE)
            {
                cell.in_cluster = true;

                if (col!=0 && blue_clusters.size()!=0)
                {
                    Cell last_element = blue_clusters.back().elements.back();
                    if (has_neighboring_cluster(last_element,cell))
                    {
                        cell.cluster_id = last_element.cluster_id;
                        blue_clusters.back().elements.push_back(cell);
                        std::cout << sym;
                        continue;
                    }
                    
                }
                Cluster new_cluster;
                new_cluster.elements.push_back(cell);
                blue_clusters.push_back(new_cluster);
                cell.cluster_id = blue_clusters.size();
            }
            
            std::cout << sym;
        }
        std::cout << '\n';
    }

    for (size_t i = 0; i < blue_clusters.size(); i++)
    {
        for (size_t j = i+1; j < blue_clusters.size(); j++)
        {
            if (can_clusters_pair(blue_clusters[i],blue_clusters[j]))
            {
                //std::cout << "[" <<i << " -> " << j << "]";
                blue_clusters[i].elements.insert( blue_clusters[i].elements.end(), blue_clusters[j].elements.begin(), blue_clusters[j].elements.end() );
                blue_clusters[j].is_marked_for_deletion = true;
            } 
        }
          
    }

    for (size_t i = 0; i < blue_clusters.size();)
    {
        if (blue_clusters[i].is_marked_for_deletion)
        {
            auto clusterToRemove = blue_clusters.begin() + i;
            blue_clusters.erase(clusterToRemove);
        }
        else
        {
            // Only increment 'i' if an element is not removed
            ++i;
        }
    }

    std::cout << "\n\nClustering blue balls: ";
    for (size_t i = 0; i < blue_clusters.size(); i++)
    {
        std::cout <<'\n';
        int row = 0;
        int sum_row_pos = 0;
        int sum_col_pos = 0;
        for (size_t j = 0; j < blue_clusters[i].elements.size(); j++)
        {
            sum_col_pos+=blue_clusters[i].elements[j].position.column;
            sum_row_pos+=blue_clusters[i].elements[j].position.row;
            if (row != blue_clusters[i].elements[j].position.row)
            {
                row = blue_clusters[i].elements[j].position.row;
                std::cout <<'\n';  
                std::cout <<row<<": ";
            }
            
            std::cout << '['<< blue_clusters[i].elements[j].position.column<< ']';
        }
        blue_clusters[i].middle_point.row = sum_row_pos/blue_clusters[i].elements.size();
        blue_clusters[i].middle_point.column = sum_col_pos/blue_clusters[i].elements.size();

        std::cout << "\nav row: " << blue_clusters[i].middle_point.row;
        std::cout << "\nav col: " << blue_clusters[i].middle_point.column;
     }

    std::cout << "\n\n\nSearching for shortest path: \n\n";
    set_target(sonic,blue_clusters[0]);

    for (size_t i = 1; i < blue_clusters.size(); i++)
    {   
        int curr_diff = 
        (
            abs(sonic.current_position.column-sonic.target->middle_point.column)+
            abs(sonic.current_position.row-sonic.target->middle_point.row)
        );
        int diff_to_check = 
        (
            abs(sonic.current_position.column-blue_clusters[i].middle_point.column)+
            abs(sonic.current_position.row-blue_clusters[i].middle_point.row)
        );
        std::cout <<"Current: "<<curr_diff <<" | Candidate: "<<diff_to_check<<'\n'; 
        if (diff_to_check<curr_diff)
        {
            set_target(sonic,blue_clusters[i]);
        }
    }

    std::cout << "\nSONIC-> ROW: " << sonic.current_position.row <<" | COL: "<<sonic.current_position.column;
    std::cout << "\nTARGET CLUSTER AV-> ROW: " << sonic.target->middle_point.row <<" | COL: "<<sonic.target->middle_point.column ;
    std::cout << '\n';

    std::cout << "\n\nSearching for closest cell in target cluser: \n\n";
    int closest_cell_index = 0;
    for (size_t i = 1; i < sonic.target->elements.size(); i++)
    {
        sonic.target->elements[i].position.column;
        int curr_diff = 
        (
            abs(sonic.current_position.column-sonic.target->elements[closest_cell_index].position.column)+
            abs(sonic.current_position.row-sonic.target->elements[closest_cell_index].position.row)
        );
        int diff_to_check = 
        (
            abs(sonic.current_position.column-sonic.target->elements[i].position.column)+
            abs(sonic.current_position.row-sonic.target->elements[i].position.column)
        );
        std::cout <<"Current: "<<curr_diff <<" | Candidate: "<<diff_to_check<<'\n'; 
        if (diff_to_check<curr_diff)
        {
            closest_cell_index = i;
        }
    }

    std::cout 
        << "\nTARGET CELL-> ROW: " 
        << sonic.target->elements[closest_cell_index].position.row 
        <<" | COL: "
        <<sonic.target->elements[closest_cell_index].position.column;
    
    input_file.close();
    output_file.close();

    return 0;
}
