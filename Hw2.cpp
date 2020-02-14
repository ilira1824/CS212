#include <iostream>
#include <cstdlib>

using namespace std;

//int foo(int input);

int main(int argc, char** argv) {
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
            "push EBP:"             // Function Prologue
            "mov EBP, ESP;"
            "sub ESP, 16;"
            "push EBX;"             // Preserve Registers
            "push ECX;"
            "push EDX;"

            "mov DWORD PTR [EBP - 4], 12;"      // Local Variable to hold product of for loop
            "mov EDX, 0;"                       // For loop counter
            "mov EBX, EAX;"                     // EBX is copy of EAX that function messes with
            "sub EBX, 2;"                       // Value to be used for for loop test expression
            "mov DWORD PTR [EBP - 8], EBX"      // input - 2
            
            "basecase:"             // Base case
                "cmp EAX, 1;"       // Returns 2 if the input is 1
                "je truebasecase;"
                "jmp falsebasecase;"
            "truebasecase:"
                "mov EAX, 2;"
                "ret;"
            "falsebasecase:"

            "topofloop:"            // Setting up for loop
                "cmp EDX, DWORD PTR [EBP - 8];"
                "jge endofloop;"
                "mul DWORD PTR [EBP - 4], DWORD PTR [EBP - 4], 12;"
                "add EDX, 1;"
                "jmp topofloop;"
            "endofloop:"

            "add DWORD PTR [EBP - 8], 1;" // Input - 1, input parameter for recursion call

            "push DWORD PTR [EBP - 8];" // Pushing input - 1 for next recursive call
            "call geomet;"
            "add ESP, 4;"


            "pop EDX;"              // Restore Registers
            "pop ECX;"
            "pop EBX;"

            "add ESP, 8;"           // Function Epilogue
            "pop EBP;"
            "ret;"
        "end:"

        :"=a" (series)
        :"a" (input)
    );

    cout << "f(" << input << ") = " << series << endl;
    return 0;
}

/*
int foo(int input) {
    int output, pow = 12;
    if (input == 1)
        return 2;

    for (int i = 0; i < input - 2; i++)
        pow *= 12;

    output = foo(input - 1) + (2 * pow);

    return output;
}*/