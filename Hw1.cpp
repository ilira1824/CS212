#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    int item1, item2, item3, item4,
        sub1, sub2, sub3;

    cout << "Enter first integer: ";
    cin >> item1;
    cout << "Enter second integer: ";
    cin >> item2;
    cout << "Enter first integer: ";
    cin >> item3;
    cout << "Enter second integer: ";
    cin >> item4;

  // Visual Studio style allows you to deal with C++ variables
  // directly in your inline code
    asm (
      ".intel_syntax noprefix;" 
      "sub EAX, EBX;"           // Subtract first two numbers
      "sub ECX, EDX;"           // Subtract next two numbers
      "mov EDX, EAX;"           // Copy first subtraction to register for future
      "add EAX, ECX;"            // Add both subtractions
      :"=d" (sub1), "=c" (sub2), "=a" (sub3)
      :"a" (item1), "b" (item2), "c" (item3), "d" (item4)  
    );

    cout << "The first difference: " << sub1 << endl;
    cout << "The second difference: " << sub2 << endl;
    cout << "Differences added together: " << sub3 << endl;


    return 0;
}