#include <iostream>
using namespace std;

int main(){

    // finding factorial of any number
    int num = 1;
    cout << "Enter a number: ";
    cin >> num;
    int factorialNum = 1;
    int tempNum = 1;

    for (int i = 1; i <= num; i++){
        tempNum = tempNum * i;
    }
    num = tempNum;
    printf("Factorial: %d \n",num);
    return 0;
}

