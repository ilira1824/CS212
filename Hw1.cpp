#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    int item1, item2, sum;

    cout << "Enter first integer: ";
    cin >> item1;
    cout << "Enter second integer: ";
    cin >> item2;

  // Visual Studio style allows you to deal with C++ variables
  // directly in your inline code
    asm (
        ".intel_syntax noprefix;" 
        "mov EBX, item2;" 
        "mov EAX, item1;" 
        "add EAX, EBX;" 
        "mov sum, EAX;"
    );

    cout << "The sum is " << sum << endl;

    return 0;
}