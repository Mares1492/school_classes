#include <iostream>
#include <vector>
#include <algorithm>

struct State {
    int nr, stat1, stat2, stat3;
};

bool can_satisfy_requirements(const std::vector<State>& states) {
    for (int i = 1; i < states.size(); i++) {
        if (states[i - 1].nr > states[i].nr) {
            return false;
        }
    }
    return true;
}

bool find_weights_and_check_requirements(std::vector<State>& states, const std::vector<std::pair<int, int>>& requirements) {
    double left = 0.0, right = 1.0;
    int iterations = 100;

    while (iterations--) {
        double mid = (left + right) / 2;
        double lambda1 = mid;
        double lambda2 = (1 - mid) / 2;
        double lambda3 = (1 - mid) / 2;

        std::vector<double> weights = {lambda1, lambda2, lambda3};
        
        std::sort(states.begin(), states.end(), [&weights](const State& a, const State& b) {
            return (a.stat1 * weights[0] + a.stat2 * weights[1] + a.stat3 * weights[2]) >
                   (b.stat1 * weights[0] + b.stat2 * weights[1] + b.stat3 * weights[2]);
        });

        if (can_satisfy_requirements(states)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left >= 1.0 - 1e-9;
}

int main() {
    int tests;
    std::cin >> tests;
    for (int test_nr = 0; test_nr < tests; test_nr++) {
        int states, requirements;
        std::cin >> states >> requirements;
        std::vector<State> states_vector(states);
        std::vector<std::pair<int, int>> requirements_vector;

        for (int state_index = 0; state_index < states; state_index++) {
            states_vector[state_index].nr = state_index + 1;
            std::cin >> states_vector[state_index].stat1 >> states_vector[state_index].stat2 >> states_vector[state_index].stat3;
        }

        for (int requirement_index = 0; requirement_index < requirements; requirement_index++) {
            int state_a_nr, state_b_nr;
            std::cin >> state_a_nr >> state_b_nr;
            requirements_vector.push_back({state_a_nr, state_b_nr});
        }

        if (find_weights_and_check_requirements(states_vector, requirements_vector)) {
            std::cout << "JAH" << std::endl;
        } else {
            std::cout << "EI" << std::endl;
        }
    }

    return 0;
}
