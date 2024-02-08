#include <iostream>
#include <memory>
#include <string>

enum class StrategyType{
    Idle,
    Patrol,
    Attack
};

struct Position
{
    int x=0,y=0;
    Position(){}
    Position(const int xToSet,const int yToSet):x(xToSet),y(yToSet){};
};


class Entity{
    public:
        Entity(const std::string name,const int x,const int y):_name(name){
            _position.x = x; 
            _position.y = y;
        }
        Position getPosition(){
             
            return _position;
        }
        void setPosition(const int x,const int y){
            _position.x = x; 
            _position.y = y;
        }
        std::string getName(){
            return _name;
        }
    private:
        Position _position;
        std::string _name;
};

class Strategy{
    public:
        //mb bool to check if success
        virtual void move(Entity& entity,Position& toPosition) const = 0;
        virtual void interact(Entity& entity,std::string name) const = 0;

};

class Idle: public Strategy{

    public:
        void move(Entity& entity,Position& toPosition) const override{
            std::cout << entity.getName() << " has moved from ";
            Position position = entity.getPosition();
            std::cout << std::to_string(position.x) <<"|"<< std::to_string(position.y);
            std::cout << " to " << std::to_string(toPosition.x) <<"|"<< std::to_string(toPosition.y)<< "\n";
            //..
        }
        void interact(Entity& entity,std::string name) const override{
            std::cout << entity.getName() << " has touched the " << name << "\n";
            //..
        }
};

class Patrol: public Strategy{

    public:
        void move(Entity& entity,Position& toPosition) const override{
            std::cout << entity.getName() << " is patrolling from ";
            Position position = entity.getPosition();
            std::cout << std::to_string(position.x) <<"|"<< std::to_string(position.y);
            std::cout << " to " << std::to_string(toPosition.x) <<"|"<< std::to_string(toPosition.y)<< "\n";
            //..
        }
        void interact(Entity& entity,std::string name) const override{
            std::cout << entity.getName() << " has examined the " << name << "\n";
            //..
        }
};

class Attack: public Strategy{

    public:
        void move(Entity& entity,Position& toPosition) const override{
            std::cout << entity.getName() << " has rushed from ";
            Position position = entity.getPosition();
            std::cout << std::to_string(position.x) <<"|"<< std::to_string(position.y);
            std::cout << " to " << std::to_string(toPosition.x) <<"|"<< std::to_string(toPosition.y)<< "\n";
            //..
        }
        void interact(Entity& entity,std::string name) const override{
            std::cout << entity.getName() << " has crushed the " << name << "\n";
            //..
        }
};


class Context {
public:
    Context(std::unique_ptr<Strategy> strategy) : _strategy(std::move(strategy)) {}

    void move(Entity& entity, Position position) {
        _strategy->move(entity, position);
        entity.setPosition(position.x,position.y);
    }

    void interact(Entity& entity,std::string name) {
        _strategy->interact(entity,name);
    }

    void setStrategy(std::unique_ptr<Strategy> newStrategy) {
        _strategy = std::move(newStrategy);
    }

private:
    std::unique_ptr<Strategy> _strategy;
};


int main(){
    std::unique_ptr<Strategy> idleStr = std::make_unique<Idle>();
    Entity hero("Hero",5,6);
    std::cout << "\nIdle Strategy:\n";
    Context gameContext(std::move(idleStr));
    gameContext.move(hero,Position(3,6));
    //instead of the string name there should be a ref to the object 
    gameContext.interact(hero,"wall");
    
    std::cout << "\n\nPatrol Strategy:\n";
    std::unique_ptr<Strategy> patrolStr = std::make_unique<Patrol>();
    gameContext.setStrategy(std::move(patrolStr));
    gameContext.move(hero, Position(2,4));
    gameContext.interact(hero,"trail");

    std::cout << "\n\nAttack Strategy:\n";
    std::unique_ptr<Strategy> attackStr = std::make_unique<Attack>();
    gameContext.setStrategy(std::move(attackStr));
    gameContext.move(hero, Position(4,8));
    gameContext.interact(hero,"vase");

    std::cout << std::endl;
    return 0;
}