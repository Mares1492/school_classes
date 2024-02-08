#include <iostream>
#include <list>

int main() {
    int gnomes;
    long long total_length = 0,prev_length, curr_pos = 0, last_pos=-1;
    std::cin >> gnomes;
    std::list<long long> positions;
    for (int i = 0; i < gnomes; i++) {
        long long piece;
        std::cin >> piece;
        if (piece < 1 || piece > 1000000)
        {
            std::cout << "EI" << std::endl;
            return 0;
        }
        prev_length = total_length;
        total_length += piece;
        positions.emplace_back(curr_pos);
        if (last_pos >= curr_pos)
        {
            std::cout << "EI" << std::endl;
            return 0;
        }
        last_pos = curr_pos;
        
        curr_pos = (total_length * 2) - curr_pos;
        //problem is HERE ↓
        //last test case is failing while being on i = 1 
        //last_pos is > than total_length but it is considered ok in this particular case
        //first fail index is 1
        if (last_pos > total_length) {
            std::cout << "EI" << std::endl;
            return 0;
        }
    }
    
    /*if (gnomes != static_cast<int>(positions.size()))
    {
        std::cout << "EI" << std::endl;
        return 0;
    }*/
    

    for (auto &&position : positions) {
        std::cout << position << " ";
    }
    std::cout << std::endl;

    return 0;
}
