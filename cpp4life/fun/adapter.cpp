#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

enum class WeaponType {
    Bow,
    Sword,
    Caestus,
};
class Buff
{
    public:
        virtual int getPowerModifier() const = 0;
        virtual int getSpeedModifier() const = 0;
        virtual int getDistanceModifier() const = 0;
        virtual int getRadiusModifier() const = 0;
};

//Some kind of weapon buff
class SomeKindOfWeaponBuff: public Buff
{
    public:
        int getPowerModifier() const override{
            return 2;
        }
        int getSpeedModifier() const override{
            return 2;
        }
        int getDistanceModifier() const override{
            return 3;
        }
        int getRadiusModifier() const override{
            return 3;
        }
};

class Weapon
{
    public:
        virtual std::string getName() const = 0;
        virtual int getAttackPower() const = 0;
        virtual int getAttackSpeed() const = 0;
        virtual int getAttackRadius() const = 0;
        virtual int getAttackDistance() const = 0;
        //virtual void setBuff() const = 0;//I would do it like that
        //virtual void clearBuff() const = 0; // but its another pattern
        virtual WeaponType getWeaponType() const = 0;
};

class Sword: public Weapon
{
    public:
        std::string getName() const override{
            return "sword";
        }
        int getAttackPower() const override {
            return 5;
        }
        int getAttackSpeed() const override {
            return 2;
        }
        int getAttackRadius() const override {
            return 3;
        }
        int getAttackDistance() const override{
            return 3;
        }
        WeaponType getWeaponType() const override{
            return WeaponType::Sword;
        }

};

class Caestus: public Weapon
{
    public:
        std::string getName() const override{
            return "fisting device";
        }
        int getAttackPower() const override {
            return 2;
        }
        int getAttackSpeed() const override {
            return 10;
        }
        int getAttackDistance() const override{
            return 1;
        }
        int getAttackRadius() const override{
            return 0;
        }
        WeaponType getWeaponType() const override{
            return WeaponType::Caestus;
        }
};

class Bow: public Weapon
{
    public:
        std::string getName() const override{
            return "bow";
        }
        int getAttackPower() const override {
            return 8;
        }
        int getAttackSpeed() const override{
            return 1;
        }
        int getAttackDistance() const override{
            return 10;
        }
        int getAttackRadius() const override{
            return 0;
        }
        WeaponType getWeaponType() const override{
            return WeaponType::Bow;
        }
};

/*
class SwordBuff: public WeaponBuff{
    public:
        int getRadiusModifier(){
            return 2;
        }
};

class BowBuff: public WeaponBuff{
    public:
        int getDistanceModifier(){
            return 2;
        }
};

class CaestusBuff: public WeaponBuff{
    public:
        int getPowerModifier(){
            return 3;
        }
        int getSpeedModifier(){
            return 3;
        }
};
*/
class AttackAdapter
{
    public:
        void handleAttack(std::string name,const Weapon& weapon, const Buff& weaponBuff, bool isBuffed){
            std::cout << "\n\nHero named " << name << "\nHas used a ";
            if (isBuffed)
            {
                std::cout << "BUFFED ";
            }
            std::cout <<  weapon.getName()<<"!\n";
            
            WeaponType weaponType = weapon.getWeaponType();
            switch (weaponType)
            {
            case WeaponType::Sword:
                _handleSwordAttack(weapon,weaponBuff, isBuffed);
                break;
            case WeaponType::Bow:
                _handleBowAttack(weapon,weaponBuff,isBuffed);
                break;
            case WeaponType::Caestus:
                _handleCaestusAttack(weapon,weaponBuff,isBuffed);
                break;
            default:
                std::cout << "An Error";
                break;
            }
        }
    private:
        void _handleBasicAttack(const Weapon& weapon, const Buff& weaponBuff, bool isBuffed) {
        int attackPower = weapon.getAttackPower();
        int attackSpeed = weapon.getAttackSpeed();

        if (isBuffed) {
            attackPower *= weaponBuff.getPowerModifier();
            attackSpeed *= weaponBuff.getSpeedModifier();
        }

        std::cout << "Attack power: " << attackPower << '\n';
        std::cout << "Attack speed: " << attackSpeed << '\n';
    }

    void _handleSwordAttack(const Weapon& weapon, const Buff& weaponBuff, bool isBuffed) {
        _handleBasicAttack(weapon,weaponBuff, isBuffed);
        int attackRadius = weapon.getAttackRadius();
        int attackDistance = weapon.getAttackDistance();
        if (isBuffed)
        {
            attackRadius *= weaponBuff.getRadiusModifier();
        }
        std::cout << "Attack Distance: " << attackDistance << '\n';
        std::cout << "Attack Radius: " << attackRadius << '\n';
    }

    void _handleBowAttack(const Weapon& weapon, const Buff& weaponBuff, bool isBuffed) {
        _handleBasicAttack(weapon,weaponBuff, isBuffed);
        int attackDistance = weapon.getAttackDistance();
        if (isBuffed)
        {
            attackDistance *= weaponBuff.getDistanceModifier();
        }
        std::cout << "Attack Distance: " << attackDistance << '\n';
    }

    void _handleCaestusAttack(const Weapon& weapon, const Buff& weaponBuff, bool isBuffed) {
        _handleBasicAttack(weapon,weaponBuff, isBuffed);
        int attackDistance = weapon.getAttackDistance();
        std::cout << "Attack Distance: " << attackDistance << '\n';
        // ...
    }

};

class Hero{
    private:
        int _hp = 10;
        std::string _name;
        bool _isBuffed = false;  
        std::unique_ptr<Weapon> _weapon;
        std::unique_ptr<Buff> _weaponBuff;
        AttackAdapter _attackAdapter;        
    public:
        Hero(const std::string& heroName) : _name(heroName){}

        void setWeapon(WeaponType weaponType){
            switch (weaponType)
            {
            case WeaponType::Sword:
                _weapon = std::move(std::make_unique<Sword>());
                break;
            case WeaponType::Bow:
                _weapon = std::move(std::make_unique<Bow>());
                break;
            case WeaponType::Caestus:
                _weapon = std::move(std::make_unique<Caestus>());
                break;
            }
        }

        std::string getName() const {
            return _name;
        }

        void handleAttack(){
            _attackAdapter.handleAttack
            (
                _name,
                *_weapon,
                *_weaponBuff,
                _isBuffed
            );
        }

        void toggleBuff(){
            if (_isBuffed)
            {
                _isBuffed = false;
            }
            else
            {
                if (_weapon!= nullptr)
            {
                _isBuffed = true;
                _weaponBuff = std::move(std::make_unique<SomeKindOfWeaponBuff>());
            }
            else
            {
                std::cout << "\nStrange, no weapon found\n";
            }
            }
        }
};

int main(){
    Hero hero("Bro");
    hero.setWeapon(WeaponType::Sword);
    hero.toggleBuff();
    hero.handleAttack();
    hero.toggleBuff();
    hero.handleAttack();

    Hero hero2("Magi");
    hero2.setWeapon(WeaponType::Bow);
    hero2.toggleBuff();
    hero2.handleAttack();

    Hero hero3("Toro");
    hero3.setWeapon(WeaponType::Bow);
    //hero3.toggleBuff();
    hero3.handleAttack();

    Hero hero4("Tucco");
    hero4.setWeapon(WeaponType::Caestus);
    hero4.toggleBuff();
    hero4.handleAttack();
}
