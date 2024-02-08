#include <iostream>
#include <vector>
#include <ctime>
#include <random>

#define ROBOTS 10

struct Stats
{
    int speed,durability,power;
};


//mb there is need to create sep enums for head and lower body
enum class RobotBodyType {
    Cool,
    Classic,
    Abstract,
    Modern,
    Steampunk,
    Scout,
    // ...
    Count
};

enum class RobotLeftArmType {
    Big,
    Small,
    Gatling,
    Hook,
    // ...
    Count
};

enum class RobotRightArmType {
    Gun,
    Fist,
    Sword,
    Hook,
    // ...
    Count
};

class RobotPart {
    public:
        virtual std::string getPart() const = 0;
        virtual int getSpeed() const = 0;
        virtual int getDurability() const = 0;
        virtual int getPower() const = 0;
        //virtual method for part properties ->
        //..
};

class RobotHeadCool : public RobotPart {
    public:
        std::string getPart() const override {
            return "    {@-|-@}\n";
        }

        int getSpeed() const override{
            return -1;
        }
        int getDurability() const override{
            return 2;
        }
        int getPower() const override{
            return 5;
        }
};
class RobotHeadClassic : public RobotPart {
    public:
        std::string getPart() const override {
            return "     [(o)]\n";
        }
        int getSpeed() const override{
            return 0;
        }
        int getDurability() const override{
            return 1;
        }
        int getPower() const override{
            return 3;
        }

        
};
class RobotHeadAbstract : public RobotPart {
    public:
        std::string getPart() const override {
            return "     <;_;>\n";
        }
        int getSpeed() const override{
            return 2;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 2;
        }
};
class RobotHeadModern : public RobotPart {
    public:
        std::string getPart() const override {
            return "      ,,,\n     (- -)\n";
        }
        int getSpeed() const override{
            return 3;
        }
        int getDurability() const override{
            return -1;
        }
        int getPower() const override{
            return 1;
        }
    
};

class RobotHeadSteampunk : public RobotPart {
    public:
        std::string getPart() const override {
            return "   (*******)\n  / [ ]-[ ] \\\n   \\  |||  /\n";
        }
        int getSpeed() const override{
                return -5;
        }
        int getDurability() const override{
            return 5;
        }
        int getPower() const override{
            return 5;
        }
};

class RobotHeadScout: public RobotPart {
    public:
        std::string getPart() const override {
            return "      ___\n    _/_*_\\_\n    (+)_- )\n";
        }
        int getSpeed() const override{
                return 3;
        }
        int getDurability() const override{
            return -1;
        }
        int getPower() const override{
            return 1;
        }
};

class RobotLeftArmBig : public RobotPart {
    public:
        std::string getPart() const override {
            return ">o[|";
        }
        int getSpeed() const override{
                return 1;
        }
        int getDurability() const override{
            return 2;
        }
        int getPower() const override{
            return 2;
        }
};
class RobotLeftArmSmall : public RobotPart {
    public:
        std::string getPart() const override {
            return " >=|";
        }
        int getSpeed() const override{
                return 5;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 1;
        }
};
class RobotLeftArmGatling : public RobotPart {
    public:
        std::string getPart() const override {
            return "%]=(";
        }
        int getSpeed() const override{
                return -2;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 5;
        }
};

class RobotLeftArmHook : public RobotPart {
    public:
        std::string getPart() const override {
            return "}~~~";
        }
        int getSpeed() const override{
                return 2;
        }
        int getDurability() const override{
            return -1;
        }
        int getPower() const override{
            return 2;
        }
};


class RobotRightArmHook : public RobotPart {
    public:
        std::string getPart() const override {
            return "=*<";
        }
        int getSpeed() const override{
                return 1;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 2;
        }
};

class RobotRightArmSword : public RobotPart {
    public:
        std::string getPart() const override {
            return "\\=|<o>>>>>";
        }
        int getSpeed() const override{
                return -2;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 5;
        }
};
class RobotRightArmGun : public RobotPart {
    public:
        std::string getPart() const override {
            return "\\=(o)";
        }
        int getSpeed() const override{
                return 0;
        }
        int getDurability() const override{
            return 0;
        }
        int getPower() const override{
            return 3;
        }
};
class RobotRightArmFist : public RobotPart {
    public:
        std::string getPart() const override {
            return "={|||}";
        }
        int getSpeed() const override{
                return 0;
        }
        int getDurability() const override{
            return 1;
        }
        int getPower() const override{
            return 2;
        }
};
class RobotBodyCool : public RobotPart {
    public:
        std::string getPart() const override {
            return "{<$$$>}";
        }
        int getSpeed() const override{
            return 1;
        }
        int getDurability() const override{
            return 2;
        }
        int getPower() const override{
            return 2;
        }
};
class RobotBodyClassic : public RobotPart {
    public:
        std::string getPart() const override {
            return "[|\"o\"|]";
        }
        int getSpeed() const override{
            return 1;
        }
        int getDurability() const override{
            return 3;
        }
        int getPower() const override{
            return 1;
        }
};
class RobotBodyAbstract : public RobotPart {
    public:
      std::string getPart() const override {
        return ".\\\\|//.";
    }
    int getSpeed() const override{
        return 3;
    }
    int getDurability() const override{
        return 2;
    }
    int getPower() const override{
        return 5;
    }
};
class RobotBodyModern : public RobotPart {
public:
    std::string getPart() const override {
        return "{-.-.-}";
    }
    int getSpeed() const override{
        return 3;
    }
    int getDurability() const override{
        return 4;
    }
    int getPower() const override{
        return 2;
    }
};

class RobotBodySteampunk : public RobotPart {
public:
    std::string getPart() const override {
        return "[|'|'|]";
    }
    int getSpeed() const override{
        return -3;
    }
    int getDurability() const override{
        return 5;
    }
    int getPower() const override{
        return 5;
    }
};

class RobotBodyScout : public RobotPart {
public:
    std::string getPart() const override {
        return "\\0xxx0/";
    }
    int getSpeed() const override{
        return 5;
    }
    int getDurability() const override{
        return -1;
    }
    int getPower() const override{
        return 1;
    }
};

class RobotLowerBodyScout : public RobotPart {
    public:
      std::string getPart() const override {
        return "\n    [     ]\n   _]_   _[_";
    }
    int getSpeed() const override{
        return 7;
    }
    int getDurability() const override{
        return -3;
    }
    int getPower() const override{
        return 1;
    }
};

class RobotLowerBodyCool : public RobotPart {
    public:
      std::string getPart() const override {
        return "\n   {.}'''{.}";
    }
    int getSpeed() const override{
        return 3;
    }
    int getDurability() const override{
        return 2;
    }
    int getPower() const override{
        return 1;
    }
};
class RobotLowerBodyClassic : public RobotPart {
    public:
      std::string getPart() const override {
        return "\n    /-<o>-\\\n   00     00";
    }
    int getSpeed() const override{
        return 1;
    }
    int getDurability() const override{
        return 3;
    }
    int getPower() const override{
        return 1;
    }
};
class RobotLowerBodyAbstract : public RobotPart {
    public:
      std::string getPart() const override {
        return "\n    /w/.\\w\\\n   <|/   \\|>";
    
    }
    int getSpeed() const override{
        return 4;
    }
    int getDurability() const override{
        return -1;
    }
    int getPower() const override{
        return 2;
    }
};
class RobotLowerBodyModern : public RobotPart {
    public:
        std::string getPart() const override {
            return "\n   / |-+-| \\\n   \\_/   \\_/";
        }
        int getSpeed() const override{
            return 4;
        }
        int getDurability() const override{
            return 4;
        }
        int getPower() const override{
            return 0;
        }
};
class RobotLowerBodySteampunk : public RobotPart {
public:
    std::string getPart() const override {
        return "\n   [/][|][\\]\n   [-][-][-]";
    }
    int getSpeed() const override{
        return 2;
    }
    int getDurability() const override{
        return 2;
    }
    int getPower() const override{
        return 2;
    }
};


class RobotPartCreator {
 public:
  virtual ~RobotPartCreator(){};
  virtual RobotPart* FactoryMethod() const = 0;

  std::string getRobotPart() const {
    RobotPart* robotPart = this->FactoryMethod();
    std::string robotPartToPrint = robotPart->getPart();
    delete robotPart;
    return robotPartToPrint;
  }
  
  std::string getStat() const {
    RobotPart* robotPart = this->FactoryMethod();
    std::string robotPartToPrint = robotPart->getPart();
    delete robotPart;
    return robotPartToPrint;
  }
};

class HeadCreator : public RobotPartCreator {
  public:
        HeadCreator(RobotBodyType headType = RobotBodyType::Classic) : headType_(headType) {}
        RobotPart* FactoryMethod() const override {
            switch (headType_)
            {
            case RobotBodyType::Cool:
                return new RobotHeadCool();
                break;
            case RobotBodyType::Abstract:
                return new RobotHeadAbstract();
                break;
            case RobotBodyType::Modern:
                return new RobotHeadModern();
                break;
            case RobotBodyType::Steampunk:
                return new RobotHeadSteampunk();
                break;
            case RobotBodyType::Scout:
                return new RobotHeadScout();
                break;
            default:
                return new RobotHeadClassic();
                break;
            }
        }

    private:
        RobotBodyType headType_;
};

class BodyCreator : public RobotPartCreator {
    public:
        BodyCreator(RobotBodyType bodyType = RobotBodyType::Classic) : bodyType_(bodyType) {}
        RobotPart* FactoryMethod() const override {
            switch (bodyType_)
            {
            case RobotBodyType::Cool:
                return new RobotBodyCool();
                break;
            case RobotBodyType::Abstract:
                return new RobotBodyAbstract();
            case RobotBodyType::Modern:
                return new RobotBodyModern();
                break;
            case RobotBodyType::Steampunk:
                return new RobotBodySteampunk();
                break;
            case RobotBodyType::Scout:
                return new RobotBodyScout();
                break;
            default:
                return new RobotBodyClassic();
                break;
            }
        }

    private:
        RobotBodyType bodyType_;
};

class LeftArmCreator : public RobotPartCreator {
    public:
        LeftArmCreator(RobotLeftArmType armType = RobotLeftArmType::Small) : armType_(armType) {}
        RobotPart* FactoryMethod() const override {
            switch (armType_)
            {
            case RobotLeftArmType::Big:
                return new RobotLeftArmBig();
                break;
            case RobotLeftArmType::Gatling:
                return new RobotLeftArmGatling();
            case RobotLeftArmType::Hook:
                return new RobotLeftArmHook();
                break;
            default:
                return new RobotLeftArmSmall();
                break;
            }
        }

    private:
        RobotLeftArmType armType_;
};

class RightArmCreator : public RobotPartCreator {
    public:
        RightArmCreator(RobotRightArmType armType = RobotRightArmType::Fist) : armType_(armType) {}
        RobotPart* FactoryMethod() const override {
            switch (armType_)
            {
            case RobotRightArmType::Gun:
                return new RobotRightArmGun();
                break;
            case RobotRightArmType::Sword:
                return new RobotRightArmSword();
                break;
            case RobotRightArmType::Hook:
                return new RobotRightArmHook();
                break;
            default:
                return new RobotRightArmFist();
                break;
            }
        }

    private:
        RobotRightArmType armType_;
};

class LowerBodyCreator : public RobotPartCreator {
    public:
        LowerBodyCreator(RobotBodyType bodyType = RobotBodyType::Classic) : bodyType_(bodyType) {}
        RobotPart* FactoryMethod() const override {
            switch (bodyType_)
            {
            case RobotBodyType::Cool:
                return new RobotLowerBodyCool();
                break;
            case RobotBodyType::Abstract:
                return new RobotLowerBodyAbstract();
            case RobotBodyType::Modern:
                return new RobotLowerBodyModern();
                break;
            case RobotBodyType::Steampunk:
                return new RobotLowerBodySteampunk();
                break;
            case RobotBodyType::Scout:
                return new RobotLowerBodyScout();
                break;
            default:
                return new RobotLowerBodyClassic();
                break;
            }
        }

    private:
        RobotBodyType bodyType_;
};
/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void printPart(const RobotPartCreator& creator) {
  // ...
  std::cout << creator.getRobotPart();
  // ...
}

void printStats
    (
        const RobotPartCreator& part1,
        const RobotPartCreator& part2,
        const RobotPartCreator& part3,
        const RobotPartCreator& part4,
        const RobotPartCreator& part5
    ){

    //
}

template <typename T>
T getRandomEnumValue() {
    // Generate a random index within the range of the enum values
    int randomIndex = std::rand() % static_cast<int>(T::Count);
    // Convert the random index to the enum type
    return static_cast<T>(randomIndex);
}

void printRobot(int model,bool random = false){
    std::cout << "\n\nModel nr." << model <<":\n\n";
    RobotPartCreator* robotHeadCreator;
    RobotPartCreator* robotLeftArmCreator;
    RobotPartCreator* robotBodyCreator;
    RobotPartCreator* robotRightArmCreator;
    RobotPartCreator* robotLowerBodyCreator;

    if (random)
    {
        robotHeadCreator = new HeadCreator(getRandomEnumValue<RobotBodyType>());
        robotLeftArmCreator = new LeftArmCreator(getRandomEnumValue<RobotLeftArmType>());
        robotBodyCreator = new BodyCreator(getRandomEnumValue<RobotBodyType>());
        robotRightArmCreator = new RightArmCreator(getRandomEnumValue<RobotRightArmType>());
        robotLowerBodyCreator = new LowerBodyCreator(getRandomEnumValue<RobotBodyType>());
    }
    else
    {
        std::cout << "Classic robot showcase: \n\n";
        robotHeadCreator = new HeadCreator();
        robotLeftArmCreator = new LeftArmCreator();
        robotBodyCreator = new BodyCreator(RobotBodyType::Classic);
        robotRightArmCreator = new RightArmCreator();
        robotLowerBodyCreator = new LowerBodyCreator(RobotBodyType::Classic);
    }
    printStats
        (
            *robotHeadCreator,
            *robotLeftArmCreator,
            *robotBodyCreator,
            *robotRightArmCreator,
            *robotLowerBodyCreator
        );
    printPart(*robotHeadCreator);
    printPart(*robotLeftArmCreator);
    printPart(*robotBodyCreator);
    printPart(*robotRightArmCreator);
    std::cout << "\n    ";
    printPart(*robotBodyCreator);
    std::cout << "\n    ";
    printPart(*robotBodyCreator);
    printPart(*robotLowerBodyCreator);

    delete robotHeadCreator;
    delete robotBodyCreator;
    delete robotLeftArmCreator;
    delete robotRightArmCreator;
    delete robotLowerBodyCreator;
}

int main() {
  // Seed the random number generator with the current time
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  std::cout << "\nRobot creator initialized... \n";
  for (size_t i = 1; i < ROBOTS; i++)
  {
    printRobot(i,true);
  }
  printRobot(0);
  
  return 0;
}