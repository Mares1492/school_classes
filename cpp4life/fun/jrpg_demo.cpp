#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <iostream>
#include <fstream>

const int ROOMS_NUMBER = 6;
const int MAX_EXP = 3;
const std::string input_file_path = "../saves/simpleSave.txt";
const std::string output_file_path = "../saves/simpleSave.txt";

enum States {IDLE,ACTIVE,PASSIVE,NONE};

enum ObjTypes{
    MONSTER,
    VASE,
    EXP,
    COIN,
    NOTHING,
    PLAYER
};

struct Position
{
    int row=0,col=0;
    Position(){}
    Position(int initRow,int initCol):row(initRow),col(initCol){}

    bool operator ==(const Position& posToCheck)const {
        return (row == posToCheck.row) &&(col == posToCheck.col);
    }
    bool operator != (const Position& posToCheck)const {
        return (row != posToCheck.row) || (col != posToCheck.col);
    }
};

//xor based custom position hash
namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& p) const {
            return hash<int>()(p.row) ^ hash<int>()(p.col);
        }
    };
}

std::string getObjTypeAsString(ObjTypes type){
    switch (type)
    {
    case :
        
        break;
    
    default:
        break;
    }
}

class AbstractObject{
    public:
        virtual std::string getName() const = 0;
        virtual std::string getSymbol() const = 0; 
        virtual void setPosition(Position newPosition) = 0;
        virtual Position getPosition() const = 0;
        virtual States getState() const = 0; 
        virtual ObjTypes destroy() = 0;
        virtual ObjTypes getType() const = 0;
        virtual bool handleDefence(bool isEmpowered)const = 0;
        virtual bool getIsAccessable() const = 0;
};

class Object :public AbstractObject{
    //TODO: Split Object to subclasses
    private:
        std::string name = "empty space";
        std::string symbol = " ";
        Position position;
        States state = NONE;
        ObjTypes type = NOTHING;
        ObjTypes leftOver = NOTHING;
        bool isAccessable = true;

        void defineObj(ObjTypes typeToSet){
            switch (typeToSet)
            {
            case VASE:
                symbol = "v";
                name = "vase";
                type = VASE;
                leftOver = EXP;
                isAccessable = false;
                break;
            case EXP:
                symbol = "x";
                name = "experience";
                type = EXP;
                break;
            case COIN:
                symbol = "c";
                type = COIN;
                name = "coin";
                break;
            default:
                return;
            }
            state = PASSIVE;
        };

    public:
        Object(){};

        Object(ObjTypes type){
            defineObj(type);
        };

        std::string getSymbol() const override{
            return symbol;
        }

        std::string getName() const override{
            return name;
        }

        Position getPosition() const override{
            return position;
        }

        States getState() const {
            return state;
        }

        void setPosition(Position newPosition) override{
            position = newPosition;
        }
        ObjTypes destroy(){
            std::cout<< name <<" has been destroyed\n";
            return leftOver;
        }

        bool handleDefence(bool _isEmpowered)const override{
            //false if defence failed
            return false;
        }

        bool getIsAccessable() const override {
            return isAccessable;
        }

        ObjTypes getType() const override{
            return type;
        }

};

class Monster: public AbstractObject{
    private:
        std::string name = "Monster";
        std::string symbol = "M";
        States state = IDLE;
        Position position;
    public:

        Monster(std::string initName):name(initName){};
        Monster(){};
        
        std::string getName() const override{
            return name;
        }

        std::string getSymbol() const override{
            return symbol;
        }

        Position getPosition() const override{
            return position;
        }

        void setPosition(Position newPosition) override{
            position = newPosition;
        }

        States getState() const {
            return state;
        }

        ObjTypes destroy(){
            std::cout<< name <<" has been eliminated\n";
            return COIN;
        }
        bool handleDefence(bool isEmpowered) const override {
            return !isEmpowered;
        }
        bool getIsAccessable() const override {
            return false;
        }
        ObjTypes getType() const override {
            return MONSTER;
        }
};

class Player: public AbstractObject{
    private:
        int hp = 10;
        std::string name = "Player";
        std::string roomKey= "room-0";
        std::string symbol = "P";
        
        char direction = 'd';
        int exp = 0;
        int coins = 0;
        States state = ACTIVE;
        Position position;
    public:
        Player(){};
        Player(std::string initName):name(initName){};

        std::string getRoomKey(){
            return roomKey;
        }

        std::string getSymbol() const override{
            return symbol;
        }

        std::string getName() const override{
            return name;
        }

        void setPosition(Position newPosition) override{
            position = newPosition;
        }

        Position getPosition() const override{
            return position;
        }

        States getState() const {
            return state;
        }

        int getExp() const{
            return exp;
        }

        void setDirection(char directionToSet){
            
            if (directionToSet != direction)
            {
                std::string literal = getDirectionLiteral(directionToSet);
                if (literal != "anywhere")
                {
                    direction = directionToSet;
                    std::cout <<name<< " is now facing "<<literal<<"\n";
                }
                else
                {
                    std::cout <<name<< " isn't looking "<<literal<<"\n";
                }
                
            }        
        };

        ObjTypes destroy(){
            std::cout<< name <<" has been died";
            return NOTHING;
        }

        std::string getDirectionLiteral(char directionToSet) const {
            switch (directionToSet)
            {
            case 'w':
                return "north";
            case 'a':
                return "west";
            case 's':
                return "south";
            case 'd':
                return "east";
            default:
                return "anywhere";
            }
        }

        char getDirection() const {
            return direction;
        };

        std::string getHP(){
            return std::to_string(hp);
        }
        std::string getCoins(){
            return std::to_string(hp);
        }
        
        Position handleMove(char directionToMove){
            int rowVel = 0;
            int colVel = 0;
            switch (directionToMove)
            {
            case 'w':
                rowVel--;
                break;
            case 'a':
                colVel--;
                break;
            case 's':
                rowVel++;
                break;
            case 'd':
                colVel++;
                break;
            default:
                std::cout << "Unknown direction: "<<directionToMove<<"\n";
                return position;
            }
            return Position(position.row+rowVel,position.col+colVel);
        }

        Position handleAttack(){
            return handleMove(direction);
        }

        bool handleDefence(bool _isEmpowered) const override{
            return false;
        }

        void incrementExp(){
            exp++;
        }

        void incrementExpByValue(int value){
            exp+=value;
        }

        void incrementCoins(){
            coins++;
        }

        void incrementCoinsByValue(int value){
            coins+=value;
        }

        void displayStatBasedOnFieldRowIndex(int i){
            std::cout <<"  ";
            switch (i)
            {
            case 0:
                std::cout << "name: "<<name;
                break;
            case 1:
                std::cout << "HP: "<<hp;
                break;
            case 2:
                std::cout << "Exp: "<<exp;
                break;
            case 3:
                std::cout << "Coins: "<<coins;
                break;
            case 4:
                std::cout << "Row: "<<position.row <<"|Col: "<<position.col; 
                break;
            default:
                break;
            }
        }
        bool getIsAccessable() const override {
            return true;
        }
        ObjTypes getType() const override{
            return PLAYER;
        }

};

Player player;

class Room {
    public:
        Room(std::string key,int sizeToSet):_key(key), _size(sizeToSet){
            std::cout << "<<ROOM INIT>>\n";

            // Resize the vector to sizeToSet
             _tiles.resize(sizeToSet);

            // Initialize each element with a unique_ptr to a base Object instance
            for (int i = 0; i < sizeToSet; ++i) {
                _tiles[i].resize(sizeToSet);
                for (int j = 0; j < sizeToSet; ++j) {
                    _tiles[i][j] = std::make_unique<Object>();
                }
            }
        };

        bool attackTile(Position positionToAttack,bool isEmpowered){
            States objState = _tiles[positionToAttack.row][positionToAttack.col]->getState();
            if (objState != NONE)
            {
                if ((_tiles[positionToAttack.row][positionToAttack.col]->handleDefence(isEmpowered)))
                {
                    return false;
                }
                ObjTypes leftOver =  _tiles[positionToAttack.row][positionToAttack.col]->destroy();
                if (leftOver==NOTHING)
                {
                    _tiles[positionToAttack.row][positionToAttack.col] = std::make_unique<Object>();
                }
                else
                {
                    _tiles[positionToAttack.row][positionToAttack.col] = std::make_unique<Object>(leftOver);
                }
                return true;
            }
            std::cout << "There is nothing to attack\n";
            return false;    
        };

        void moveObject(Position oldPosition,Position newPosition){
            _tiles[newPosition.row][newPosition.col] = std::move(_tiles[oldPosition.row][oldPosition.col]);
            _tiles[oldPosition.row][oldPosition.col] = std::make_unique<Object>();
        }

        bool isWithinBounds(Position position) {
            if (position.row < 0 || position.row >= _size) {
                std::cout << "Wall";
                return false;
            }
            if (position.col < 0 || position.col >= _size) {
                std::cout << "Wall";
                return false;
            }
            return true;
        }
        
        bool isTileAccessable(Position position){
            bool isAccessable = _tiles[position.row][position.col]->getIsAccessable();
            if (!isAccessable)
            {
                std::cout << "Looks like a "<< _tiles[position.row][position.col]->getName()<<" is blocking this path\n";
            }
            
            return isAccessable;
            
        };

        ObjTypes getPositionObjType(Position position){
            ObjTypes positionObjType = _tiles[position.row][position.col]->getType();
            return positionObjType;
        };

        void displayTiles(Player& p) const{
            std::cout << "\n";
            for (int i = 0; i < _size; ++i) {
                for (int j = 0; j < _size; ++j) {
                    std::cout << "[" << _tiles[i][j]->getSymbol() << "]";
                }
                p.displayStatBasedOnFieldRowIndex(i);
                std::cout << "\n";
            }
        }
        void setObjectToTile(std::unique_ptr<AbstractObject> objectPtr, Position position) {
            _tiles[position.row][position.col] = std::move(objectPtr);
            std::cout << _tiles[position.row][position.col]->getName() << " is now set to " << position.row << "|" << position.col << " of " << _key << "\n";
        }

        void setNeibour(std::string key,std::string direction){
            _neibours[direction] = key;
        }

        int  getRandomPosition() const {
            return std::rand() % _size;
        }

        std::string getDataToSave(){
            std::string dataString = "[";
            for (int row = 0; row < _size; ++row) {
                for (int col = 0; col < _size; ++col) {
                    if(_tiles[row][col]->getType()!=NOTHING){
                        dataString+="{row:"+std::to_string(row)+",col:"+std::to_string(col)+",type:"+_tiles[row][col]->getType()+"},";
                    };
                }
                std::cout << "]\n";
            }
            
            return dataString;
        }

    private:
        std::string _key;
        int _size;
        std::unordered_map<std::string,std::string> _neibours = {{"up", ""}, {"left", ""},{"down",""},{"right",""}};
        std::vector<std::vector<std::unique_ptr<AbstractObject>>> _tiles;
};

std::unordered_map<std::string, Room> rooms;

bool open_input_file(std::ifstream& input_file) {
    input_file.open(input_file_path);
    return input_file.is_open();
}

void loadGame(const Room& targetRoom){
    std::ifstream input_file;
    if (!open_input_file(input_file)) {
        std::cerr << "Error opening input file: " << input_file_path << "\n";
    }
    std::cout << "Save is loaded";
}

void saveGame(std::string roomData){
    
    std::ofstream output_file;
    output_file.open (output_file_path);
    output_file << "room:\n "<<roomData<<"\nplayer:\nroomKey: "<<player.getRoomKey()<<"\nname: "<<player.getName()<<"\nhp: "<<player.getHP()<<"\nexp: "<<player.getExp()<<"\ncoins: "<<player.getCoins()<<"\nrow: "<<player.getPosition().row<<"\ncol: "<<player.getPosition().col<<"\n";
    output_file.close();
    std::cout << "Game is saved\n";
}


void displayRoom(std::string roomID){
    
    auto it = rooms.find(roomID);
    if (it != rooms.end()) {

        it->second.displayTiles(player);  // Display the Room's information
    } else {
        std::cout << "Room not found.\n";
    }
}


void handleLootPick(ObjTypes& typeOfObject){
    switch (typeOfObject)
    {
    case COIN:
        std::cout << "Coin was collected\n";
        player.incrementCoins();
        break;
    case EXP:
        std::cout << "Exp was gained\n";
        player.incrementExp();
        break;
    
    default:
        break;
    }
}


bool handleAction(Room& targetRoom){
    char input = '.';
    
    while (input != 'w' && input != 'a'  && input != 's'  && input != 'd'  && input != 'f' && input != 'o' && input != 'l' && input != 'k')
    {
        std::cout << "Controller Input: ";
        input = std::cin.get();

        // Clear the input buffer to discard any remaining characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "\n---------------\n";
    bool isInputNotExit = input != 'o';
    if(input=='f'){
        Position attackPosition = player.handleAttack();
        bool isEmpowered = (player.getExp()==MAX_EXP);
        bool success = targetRoom.attackTile(attackPosition,isEmpowered);
    }
    else if(input == 'k'){
        saveGame(targetRoom.getDataToSave());
    }
    else if(input == 'l'){
        loadGame(targetRoom);
    }
    else if(isInputNotExit){
        std::cout << "Moving " << player.getDirectionLiteral(input)<<"\n"; 
        Position newPosition = player.handleMove(input);
        player.setDirection(input);
        if (targetRoom.isWithinBounds(newPosition) && targetRoom.isTileAccessable(newPosition))
        {
            ObjTypes typeOfObjNextTile = targetRoom.getPositionObjType(newPosition);
            handleLootPick(typeOfObjNextTile);
            Position oldPosition = player.getPosition();
            targetRoom.moveObject(oldPosition,newPosition);
            player.setPosition(newPosition);
        }
    }

    return isInputNotExit;
}

Position generateUniquePosition(const Room& targetRoom, std::unordered_set<Position>& usedPositions) {
    int randomRow, randomCol;
    Position newPosition(0, 0);

    do {
        randomRow = targetRoom.getRandomPosition();
        randomCol = targetRoom.getRandomPosition();
        newPosition = Position(randomRow, randomCol);
    } while (usedPositions.count(newPosition) > 0);

    usedPositions.insert(newPosition);

    // Perform your actions with the unique position
    return newPosition;
}

int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int roomSizes[6] = {5,6,7,8,9,10};
    int roomSizeCounter = 0;
    int isPendingInput = true;
    std::unordered_set<Position> usedPositions;
    
    for (int r = 0; r < ROOMS_NUMBER; r++) {
        int roomSize = roomSizes[roomSizeCounter];
        std::string key = "room-" + std::to_string(r);

        rooms.insert(std::make_pair(key, Room(key,roomSize)));

        // Increment the counter and reset if necessary
        roomSizeCounter++;
        if (roomSizeCounter>5)
        {
            roomSizeCounter = 0;
        }
    
        std::cout << roomSizeCounter << "\n";   
    }

    std::unique_ptr<Player> playerPtr = std::make_unique<Player>(player);
    Room& targetRoom = rooms.at(player.getRoomKey());
    player.setPosition(generateUniquePosition(targetRoom, usedPositions));
    targetRoom.setObjectToTile(std::move(std::make_unique<Object>(VASE)),generateUniquePosition(targetRoom, usedPositions));
    targetRoom.setObjectToTile(std::move(std::make_unique<Object>(VASE)),generateUniquePosition(targetRoom, usedPositions));
    targetRoom.setObjectToTile(std::move(std::make_unique<Object>(VASE)),generateUniquePosition(targetRoom, usedPositions));
    targetRoom.setObjectToTile(std::move(std::make_unique<Monster>()),generateUniquePosition(targetRoom, usedPositions));
    targetRoom.setObjectToTile(std::move(playerPtr),player.getPosition());

    displayRoom(player.getRoomKey());   
    while (isPendingInput)
    {   
        isPendingInput = handleAction(targetRoom);
        displayRoom(player.getRoomKey());  
    }
        
    return 0;
}