#include <iostream>
#include <string>
#include <memory>

enum class InputType{
    Idle,
    TargetInSight,  
    TargetLost,
    Escape,
    Attack,
};  

enum class State{
    Idle,
    Alert,
    Chase,
    Patrol,
    Attack,
    Escape,
};

struct Position
{
    int x=0,y=0;
    Position(){}
    Position(const int xToSet,const int yToSet):x(xToSet),y(yToSet){};
};

class Test{
    public:
        virtual void test() const = 0;
};


class Entity{
    public:
        Entity() = default;
        virtual bool getIsValidTarget() const = 0;
        virtual int getDistance(Position position) const = 0;
        virtual std::string getName() const  = 0;
};

class Nobody: public Entity{
    public:
        Nobody(){};
        bool getIsValidTarget() const override{
            return false;
        }
        std::string getName() const override {
            return "nobody";
        }
        int getDistance(Position position) const override {
            std::cout << "Nobody getDistance call: "<<position.x<<"|"<<position.y<<std::endl;
            return 0;
        }
};

class Human: public Entity{
    public:
        Human(std::string name,Position position):_name(name),_position(position){}

        int getDistance(Position position) const override{
            int x = abs(position.x - _position.x);
            int y = abs(position.y - _position.y);
            return x+y;
        };

        void setTarget(std::shared_ptr<Entity> newTarget,bool isIdleTarget) {
            _target = newTarget;
            std::cout << _name << " is now targeting "<< _target->getName();
            if (!isIdleTarget)
            {
                _setState(State::Alert);
                std::cout<<" and is in alert state";
            }
            std::cout<<"\n";
        }

        Position getPosition(){
            return _position;
        }

        State getState(){
            return _state;
        };

        std::string getName() const override{
            return _name;
        };

        void moveTo(Position position){
            std::cout << _name << " has moved from " << _position.x <<'|'<<_position.y<<" to "<< position.x <<'|'<<position.y<<"\n";
            _position = position;
        }
        
        bool getIsValidTarget() const override{
            return true;
        }

        void printCurrentState(){
            switch (_state)
            {
            case State::Idle:
                std::cout<< _name <<" is idle";
                break;
            case State::Alert:
                std::cout<< _name <<" is alert";
                break;
            case State::Chase:
                std::cout<< _name <<" is chasing "<< _target->getName();
                break;
            case State::Attack:
                std::cout<< _name <<" is attacking "<< _target->getName();
                break;
            case State::Patrol:
                std::cout<< _name <<" is patrolling";
                break;
            case State::Escape:
                std::cout<< _name <<" is running for his life";
                break;
            }
            std::cout << "\n";
        }

        void setStateBasedOnInput(InputType input){
            
            if (input == InputType::Idle){
                _setState(State::Idle);
                setTarget(std::make_unique<Nobody>(),true);
                return;
            }
            
            switch (_state)
            {
            case State::Alert:
                _handleAlertStateSwitch(input);
                break;
            case State::Chase:
                _handleChaseStateSwitch(input);
                break;
            case State::Idle:
                _handleIdleStateSwitch(input);
                break;
            case State::Attack:
                _handleAttackStateSwitch(input);
                break;
            default:
                std::cout << "Required state switch has not been implemented\n";
            }
        }
    private:
        std::string _name;
        Position _position;
        State _state = State::Idle;
        std::shared_ptr<Entity> _target = std::make_shared<Nobody>();
        int _attackDistance = 2;

        void _handleAttackStateSwitch(InputType input){
            switch (input)
            {
            case InputType::Attack:
                std::cout << _name << " tries to attack " << _target->getName();
                if (_canAttackTarget())
                {
                    std::cout << " and succeedes\n";
                    // .. hit logic
                }
                else
                {
                    _setState(State::Chase);
                    std::cout 
                    << " but missed"
                    << " and is now chasing "
                    << _target->getName()
                    << "\n";
                }
                break;
            default:
                break;
            }
        }

        void _handleChaseStateSwitch(InputType input){
            switch (input)
            {
            case InputType::TargetLost:
                _loseTarget();
                break;
            
            case InputType::Attack:
                std::cout << _name << " tries to attack " << _target->getName();

                if (_canAttackTarget())
                {
                    std::cout << " and succeedes\n";
                    _setState(State::Attack);
                    std::cout<<_name<<" is now attacking "<<_target->getName()<<"\n";
                    
                }
                else
                {
                    std::cout << " but misses\n";
                }
                
            default:
                break;
            }
        };

        void _handleIdleStateSwitch(InputType input){
            switch (input)
            {
            case InputType::Escape:
                _setState(State::Escape);
                std::cout<<_name<<" is now running for his life\n";
                break;
            default:
                std::cout << "Input is not implemented for idle state\n";
                break;
            }
        }

        void _handleAlertStateSwitch(InputType input){
            switch (input)
            {
            case InputType::TargetInSight:
                if (_target->getIsValidTarget())
                {   
                    std::cout << _name <<"s distance to target: "<<_target->getDistance(getPosition())<<"\n";
                    if (_canAttackTarget())
                    {
                        _setState(State::Attack);
                        std::cout<<_name<<" is now attacking "<<_target->getName()<<"\n";
                    }
                    else
                    {
                        _setState(State::Chase);
                        std::cout<<_name<<" is now chasing "<<_target->getName()<<"\n";
                    }
                }
                else
                {
                    setStateBasedOnInput(InputType::Idle);
                    std::cout << _name<<": must be nothing...\n";
                }
                break;
            case InputType::TargetLost:
                _loseTarget();
                break;
            case InputType::Escape:
                _setState(State::Escape);
                std::cout << _name <<" is terrified and runs away\n";
                break;
            case InputType::Attack:
                //handle switch from alert to attack
                break;
            case InputType::Idle:
                //not possible
                break;
            }
        }
        
        //bool in real project
        void _setState(State state){
            _state = state;
        }

        void _loseTarget(){
            _setState(State::Alert);
            std::cout<< _name << " has lost his target out of sight\n";
            setTarget(std::make_unique<Nobody>(),true);
        }

        bool _canAttackTarget(){
            return _target->getDistance(getPosition()) <= _attackDistance;
        }
};


int main(){
    /*gameLoop() call
    should do something based on entity state
    */
    std::cout <<"\n";
    std::shared_ptr<Human> bob = std::make_shared<Human>("Bob", Position(1,2));
    bob->printCurrentState();
    std::shared_ptr<Human> mike = std::make_shared<Human>("Mike", Position(4,6));
    mike->printCurrentState();
    std::cout <<"\n";
    mike->setTarget(bob, false);
    mike->setStateBasedOnInput(InputType::TargetInSight);
    mike->moveTo(Position(2,1));
    mike->setStateBasedOnInput(InputType::Attack);
    std::cout <<"\n";
    bob->setStateBasedOnInput(InputType::Escape);
    bob->moveTo(Position(3,4));
    mike->setStateBasedOnInput(InputType::Attack);
    std::cout <<"\n";
    bob->moveTo(Position(7,8));
    mike->setStateBasedOnInput(InputType::TargetLost);
    std::cout <<std::endl;
   
   return 0;
}
