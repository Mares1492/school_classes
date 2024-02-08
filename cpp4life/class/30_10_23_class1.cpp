#include <iostream>

struct Coords{
    int x,y;
};

class Frog {
    private:
        int x,y;
    public:
        Frog(int x,int y){
            this ->x = x;this->y = y;
        }

        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
        
        bool move(std::string move_dir){
            if (move_dir == "UP")
            {
                y--;
                return true;
            }
            if (move_dir == "RIGHT")
            {
                x++;
                return true;
            }
            if (move_dir == "DOWN")
            {
                y++;
                return true;
            }
            if (move_dir == "LEFT")
            {
                x--;
                return true;
            }
            return false;
        }

        void get_position(){
             
        }
    
};

int main(){
    Frog frog(2,3);
    int move = true;
    while (move)
    {
        std::string move_input;
        std::cin >> move_input;
        move = frog.move(move_input);
        frog.get_position();
    }
    std::cout << "Not moving anymore\n";
}