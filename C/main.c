
#include <stdio.h>
#include <math.h>

void triangleSpecsPrinter(){ // task 1: prints the area and perimeter of a triangle
    float a, b, s, p;
    printf("\n\nThis program prints the area and perimeter of a triangle.");
    printf("\nEnter side a: ");
    scanf("%f", &a);
    printf("\nEnter side b: ");
    scanf("%f", &b);
    s = (a * b) / 2;
    p = a + b + sqrtf(a * a + b * b);
    if(s == (int)s){
        printf("\nArea: %d", (int)s);
    } else {
        printf("\nArea: %.2f", s);
    }
    if(p==(int)p){
        printf("\nPerimeter: %d", (int)p);
    } else {
        printf("\nPerimeter: %.2f", p);
    }
}

void quadraticEquationSolver(){ // task 2: solves a quadratic equation
    float a, b, c, x1, x2, d;
    printf("\n\nThis program solves a quadratic equation.");
    printf("\nEnter a: ");
    scanf("%f", &a);
    printf("\nEnter b: ");
    scanf("%f", &b);
    printf("\nEnter c: ");
    scanf("%f", &c);
    d = b * b - 4 * a * c;
    if(d < 0){
        printf("\nNo real roots");
    } else if(d == 0){
        x1 = -b / (2 * a);
        if(x1 == (int)x1){
            printf("\nRoot: %d", (int)x1);
        } else {
            printf("\nRoot: %.2f", x1);
        }
    } else {
        x1 = (-b + sqrtf(d)) / (2 * a);
        x2 = (-b - sqrtf(d)) / (2 * a);
        if(x1 == (int)x1){
            printf("\nRoot 1: %d", (int)x1);
        } else {
            printf("\nRoot 1: %.2f", x1);
        }
        if(x2 == (int)x2){
            printf("\nRoot 2: %d", (int)x2);
        } else {
            printf("\nRoot 2: %.2f", x2);
        }
    }
}
void operationOnChoice(){
    int choice;
    float a, b;
    printf("\n\nThis program performs an operation on two numbers.");
    printf("\nEnter a: ");
    scanf("%f", &a);
    printf("\nEnter b: ");
    scanf("%f", &b);
    printf("Choose an operation: 1. Summation, 2. Subtraction, 3. Multiplication, 4. Division , 5. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if(a==(int)a|| b==(int)b){
                printf("\nSummation: %d", (int)(a + b));
            } else {
                printf("\nSummation: %.2f", a + b);
            }
            break;
        case 2:
            if(a==(int)a|| b==(int)b){
                printf("\nSubtraction: %d", (int)(a - b));
            } else {
                printf("\nSubtraction: %.2f", a - b);
            }
            break;
        case 3:
            if(a==(int)a|| b==(int)b){
                printf("\nMultiplication: %d", (int)(a * b));
            } else {
                printf("\nMultiplication: %.2f", a * b);
            }
            break;
        case 4:
            if(b == 0){
                printf("\nDivision by zero");
            } else if(a==(int)a|| b==(int)b){
                printf("\nDivision: %d", (int)(a / b));
            } else {
                printf("\nDivision: %.2f", a / b);
            }
            break;
        default:
            printf("\nInvalid choice");
    }
}

void findSecondBiggestNumber(){
    int input, max, secondMax;
    printf("\n\nThis program finds the second biggest number.");
    do{
        printf("\nEnter number of choice('0' to exit): ");
        scanf("%d", &input);
        if(input > max){
            secondMax = max;
            max = input;
        } else if(input > secondMax){
            secondMax = input;
        }
    }while(input != 0);
    printf("\nSecond biggest number: %d", secondMax);
}

int menu() {
    int choice;
    printf("\n\n0. Exit, 1. Triangle specs printer, 2. Quadratic equation solver");
    printf("\n 3. Number operation on choice, 4. Find second biggest number");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main() {

    int choice = menu();
    while(choice !=0){
        switch(choice){
            case 0:
                printf("\nExiting...");
                break;
            case 1:
                triangleSpecsPrinter();
                break;
            case 2:
                quadraticEquationSolver();
                break;
            case 3:
                operationOnChoice();
                break;
            case 4:
                findSecondBiggestNumber();
                break;
            case 5:

                break;
            default:
                printf("\nInvalid choice");
        }
        choice = menu();
    }
    return 0;
}
