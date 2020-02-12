#include <iostream>
#include <cstdlib>

using namespace std;

int foo(int input);

int main() {
    int series, input;
    cout << "Which element of the series would you like? ";
    cin >> input;

    series = foo(input);

    cout << "f(" << input << ") = " << series << endl;
    return 0;
}

int pow(int num) {
    int result = 12;
    for (int i = 0; i < num; i++)
        result = result * 12;
    return result;
}

int foo(int input) {
    int output;
    if (input == 1)
        return 2;
    
    int pow = 12;

    for (int i = 0; i < input - 2; i++)
        pow *= 12;

    output = foo(input - 1) + (2 * pow);

    return output;
}