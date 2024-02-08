#include <iostream>
#include <string>
#include <vector>

struct lose_streak
{
    int first_day,last_day,total_lose = 0;
};

struct day{
    int nr, balance;
};

lose_streak max_lose_streak;
std::vector<day> days;

void get_max_lose_streak(lose_streak lose_streak,int current_day){
    lose_streak.total_lose+=days[current_day].balance;
    if (lose_streak.total_lose < max_lose_streak.total_lose)
    {
        lose_streak.last_day = days[current_day].nr;
        max_lose_streak = lose_streak;
    }
    if (current_day+1 < static_cast<int>(days.size()))
    {
        get_max_lose_streak(lose_streak,current_day+1);
    }  
}

int main(){
    int total_balance=0,number_of_days=0,max_lost=0,max_lost_day=0;
    std::string total_result = "EI TEA";
    std::cin >> number_of_days;
    for (int i = 1; i <= number_of_days; i++)
    {
        int local_spend = 0,local_won = 0,balance;
        std::cin >> local_spend >> local_won;
        balance = local_won-local_spend;
        total_balance += balance;
        day current_day;
        current_day.nr = i;
        current_day.balance = balance;
        days.push_back(current_day);
        
        if (max_lost > balance)
        {
            max_lost = balance;
            max_lost_day = i;
        }
    }
    for (int i = 0; i < number_of_days; i++)
    {
        if (days[i].balance<0)
        {
            lose_streak current_lose_streak;
            current_lose_streak.first_day = days[i].nr;
            current_lose_streak.total_lose = days[i].balance;
            get_max_lose_streak(current_lose_streak,i+1);
        }
        
    }
    if (total_balance < 0)
    {
        total_result = "MIINUSES";
    }
    else if (total_balance > 0)
    {
        total_result = "PLUSSIS";
    }
    else if (total_balance == 0)
    {
        total_result = "NULLIS";
    }
    
    std::cout << total_result << '\n'; 
    std::cout << max_lost_day << " " << max_lost*-1 << '\n'; 
    std::cout << max_lose_streak.first_day << " " << max_lose_streak.last_day << " " << max_lose_streak.total_lose*-1; 
    return 0;
}
