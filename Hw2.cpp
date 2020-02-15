#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int series, input;
    cout << "Which element of the series would you like? ";
    cin >> input;

    asm (
        ".intel_syntax noprefix;"
        "push EAX;"         
        "call geomet;"
        "add ESP, 8;"
        "jmp end;"

    "geomet:"
        "push EBP;"
        "mov  EBP, ESP;"
        "sub  ESP, 24;"
        "mov  DWORD PTR [EBP -12], 12;"
        "cmp  DWORD PTR [EBP + 8], 1;"
        "jne  BaseCase;"
        "mov  EAX, 2;"
        "jmp  GeometEnd;"
    "BaseCase:"
        "mov  DWORD PTR [EBP - 16], 0;"
    "ForLoop:"
        "mov  EAX, DWORD PTR [EBP+8];"
        "sub  EAX, 2;"
        "cmp  DWORD PTR [EBP-16], EAX;"
        "jge  EndOfLoop;"
        "mov  EDX, DWORD PTR [EBP-12];"
        "mov  EAX, EDX;"
        "add  EAX, EAX;"
        "add  EAX, EDX;"
        "sal  EAX, 2;"
        "mov  DWORD PTR [EBP-12], EAX;"
        "add  DWORD PTR [EBP-16], 1;"
        "jmp  ForLoop;"
    "EndOfLoop:"
        "mov  EAX, DWORD PTR [EBP+8];"
        "sub  EAX, 1;"
        "sub  ESP, 12;"
        "push EAX;"
        "call geomet;"
        "add  ESP, 16;"
        "mov  EDX, DWORD PTR [EBP-12];"
        "add  EDX, EDX;"
        "add  EAX, EDX;"
    "GeometEnd:"
        "leave;"
        "ret;"
    "end:"

        :"=a" (series)
        :"a" (input)
    );

    cout << "f(" << input << ") = " << series << endl;
    return 0;
}