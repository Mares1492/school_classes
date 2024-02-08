#include <iostream>
#include <vector>

struct State
{
    int nr,stat1,stat2,stat3;
};

bool custom_comparison(const State& a, const State& b) {
    return a.nr > b.nr;
}

int main(){
    int tests;
    std::cin >> tests;
    for (int test_nr = 0; test_nr < tests; test_nr++)
    {
        int states,requirements;
        std::cin >> states >> requirements;
        std::vector<State>states_vector(states);

        for (int state_index = 0; state_index < states; state_index++)
        {
            states_vector[state_index].nr = state_index+1;
            std::cin 
                >> states_vector[state_index].stat1 
                >> states_vector[state_index].stat2 
                >> states_vector[state_index].stat3;
        }
        for (int requirement_index = 0; requirement_index < requirements; requirement_index++)
        {
            int state_a_nr,state_b_nr;
            std::cin >> state_a_nr >> state_b_nr;
            
        }
        
    }
    
    
}