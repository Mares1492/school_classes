#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

std::mutex printMutex;
int printAllowedTo = 0;

void processStrategy(std::vector<int>& players, int from, int to,int index) {
    std::vector<int> strategy_players;
    for (int i = from; i <= to; i++) 
    {
        strategy_players.push_back(players[i]);
    }
    std::nth_element(strategy_players.begin(), strategy_players.begin() + 11, strategy_players.end());//11 smallest

    strategy_players.resize(11);
    std::sort(strategy_players.begin(),strategy_players.end());

    // Synchronize printing
    {
        std::lock_guard<std::mutex> lock(printMutex);
        while (printAllowedTo<index) {
            // Wait until it's allowed to print
        }
        printAllowedTo++;
        std::cout << strategy_players.back() << '\n';
    }
}

int main(){
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> players;
    for (int i = 0; i < N; i++)
    {
        int age;
        std::cin >> age;
        players.push_back(age);
    }

    std::vector<std::thread> threads;

    for (int i = 0; i < Q; i++) {
        int from, to;
        std::cin >> from >> to;
        threads.emplace_back(processStrategy, std::ref(players), from, to,i);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
