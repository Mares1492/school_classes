#include <iostream>
#include <list>
#include <vector>

void test(const std::vector<int>& input,int test_nr,bool isValid) {
    std::cout<<"\nTest nr: "<<test_nr<< " | isValid: "<<isValid<<"\n\n";
    int gnomes = input.size();
    long long total_length = 0, curr_pos = 0, last_pos = -1;
    std::list<int> positions;
    for (auto &&i : input) {
        std::cout << i << " ";
    }
    std::cout << "\n--------\n";
    for (int i = 0; i < gnomes; i++) {
        long long piece = input[i];
        total_length += piece;
        positions.push_back(curr_pos);
        if (last_pos >= curr_pos) // I guess issue is here or at least happens after EI
        {
            std::cout << "EI last_pos >= curr_pos | " << last_pos << " >= " << curr_pos <<'\n';
        }
        last_pos = curr_pos;
        
        curr_pos = (total_length * 2) - curr_pos;
        if (last_pos > total_length || piece < 1 || piece > 1000000) {
            std::cout << "EI last_pos > total_length | " << last_pos <<" > "<<total_length<<'\n';
        }
    }
    if (gnomes < static_cast<int>(positions.size()))
    {
        std::cout << "EI gnomes < positions.size() | " << gnomes <<" < "<<positions.size()<<'\n';
    }
    if (gnomes > static_cast<int>(positions.size()))
    {
        std::cout << "EI gnomes > positions.size() | " << gnomes <<" > "<<positions.size()<<'\n';
    }
    
    
    std::cout << "--------\n";
    for (auto &&position : positions) {
        std::cout << position << " ";
    }

    std::cout << std::endl;
}

int main() {
    // Valid input with a single gnome
    test({1}, 1, true);

    // Valid input with increasing piece lengths
    test({2, 3, 4, 5}, 2, true);

    // Invalid input with overlapping gnome positions (decreasing piece lengths)
    test({5, 4, 3, 2}, 3, false);

    // Invalid input with overlapping gnome positions (equal piece lengths)
    test({3, 3, 3, 3}, 4, false);

    // Invalid input with an overlap
    test({2, 2, 2, 1}, 5, false);

    // Valid input with a large number of gnomes and increasing piece lengths
    test({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 6, true);

    // Invalid input with overlapping gnome positions
    test({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 7, false);

    // Valid input with a large number of gnomes and increasing piece lengths
    test({3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 8, true);

    // Invalid input with an overlap
    test({5, 4, 3, 3, 2, 1}, 9, false);

    // Valid
    test({2, 3, 4, 4}, 10, true);

    // Invalid due to overlap
    test({1000, 1000, 1000}, 11, false);

    // Invalid input with a negative piece length
    test({1, 2, -3, 4}, 12, false);

    // Invalid input with a zero-length piece
    test({1, 2, 0, 4}, 13, false);

    // Valid input with a very large number of gnomes and increasing piece lengths
    test({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 14, true);

    // Invalid input with only largest possible input values due to overlap
    test({1000000, 1000000, 1000000, 1000000, 1000000}, 15, false);

    // Invalid input with some largest possible input values due to overlap
    test({5, 5000, 24, 1000000, 10}, 15, false);

    // Valid input with the largest possible single input value
    test({1000000}, 15, true);

    //Invalid input with single negative length piece
    test({-1}, 16, false);

    //Valid input due to char being taken as int
    test({'g'}, 17, true);

    test({1000000,1000000,1000000},18,false);

    test({399999,399997,399995},19,true);
    
    test({9,7,5},20,true);

    test({9,5,9},21,true);

    test({1,1},22,true);


    return 0;
}

