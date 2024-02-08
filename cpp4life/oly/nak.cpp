#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

int main(){
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> players(N);
    for (int i = 0; i < N; i++)
    {
        int age;
        std::cin >> age;
        players[i]=age;
    }
    for (int i = 0; i < Q; i++)
    {
        int from,to;
        std::cin >> from >> to;
        std::vector<int> strategy_players;
        for (int i = from; i <= to; i++) // Include strategy.to(<=)
        {
            strategy_players.push_back(players[i]);
        }
        std::nth_element(strategy_players.begin(), strategy_players.begin() + 11, strategy_players.end());//11 smallest

        strategy_players.resize(11);
        std::sort(strategy_players.begin(),strategy_players.end());

        std::cout << strategy_players.back() << '\n'; // Print the oldest of the 11 youngest players
    }
    return 0;
}
