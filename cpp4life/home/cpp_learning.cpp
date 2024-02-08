#include <iostream>
using namespace std;

void enter_integer_n_print(){
    int number;

    cout << "Enter an integer: ";
    cin >> number;

    cout << "You entered " << number;
}

void quotient_n_remainder(){
    int divisor, dividend,quotient,remainder;

    cout << "Enter dividend: ";
    cin >> dividend;

    cout << "Enter divisor: ";
    cin >> divisor;

    quotient = dividend/divisor;
    remainder = dividend % divisor;

    cout << "Quotient = " << quotient << endl;
    cout << "Remainder = " << remainder;
}

void sum_of_two_integers(){
    int first_integer,second_integer,sum;
    cout << "We are going to sum two integers\n"
    << "Enter first integer: ";
    cin >> first_integer;
    cout << "Enter second integer: ";
    cin >> second_integer;
    sum = first_integer + second_integer;

    cout << "Sum is " << sum;
}

int main(){
    //enter_integer_n_print();
    //sum_of_two_integers();
    quotient_n_remainder();

    return 0;
}
