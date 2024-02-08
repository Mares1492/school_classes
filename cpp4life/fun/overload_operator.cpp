#include <iostream>
using namespace std;

class WholeObject {
   private:
    int _minValue = 1;
    int _maxValue = 10;
    int _currentValue = _maxValue;

   public:
    WholeObject() : _currentValue(_maxValue) {}
    WholeObject(int value) : _currentValue(value) {}

    bool checkIsValid(int valueToCheck){
        return !(valueToCheck > _maxValue || valueToCheck < _minValue);
    }

    void setValue() {
        int newValue;
        cout << "Enter the value : ";
        cin >> newValue;
        if (checkIsValid(newValue))
        {
            _currentValue = newValue;  
        }
        else
        {
            _currentValue = _minValue;
        }    
    }

    void operator ! () {
        _currentValue = 0;
    }

    void operator -- (int) {
        _currentValue--;
    }

    void operator ++ (int) {
        _currentValue++;
    }

    void operator -= (int number) {
        _currentValue -= number;
    }

    void operator += (int number) {
        _currentValue += number;
    }

    //...

    void out() {
      cout<<"Output: " << _currentValue << endl;
    }
};

int main() {
    WholeObject obj;
    obj.out();
    obj--;
    obj--;
    obj.out();
    obj+=2;
    obj.out();
    !obj;
    obj.out();

    return 0;
}