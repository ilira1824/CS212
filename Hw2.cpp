#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    int series, input;
    cout << "Which element of the series would you like? ";
    cin >> input;

    // The following recursive code calculates the solution by using the formula:
    // geomet(n) = geomet(n - 1) + (2 * (12^n - 2))

    asm (
        ".intel_syntax noprefix;"                   // This doesn't seem to have an effect, I still need to compile with -masm=intel
        "push EAX;"                                 // Kickoff code, calls geomet and pushes
        "call geomet;"                              //      parameter onto the stack
        "add ESP, 4;"                               // Cleans up stack once function is done, 'Pops' it
        "jmp end;"

        "geomet:"
            "push EBP;"                            // Function Prologue
            "mov  EBP, ESP;"
            "sub  ESP, 8;"                         // Allocating space for 2 int local variables
            "mov  DWORD PTR [EBP - 4], 12;"        // Local Variable, holding value for the For Loop (int power)
            "cmp  DWORD PTR [EBP + 8], 1;"         // Base Case Statement: If input is 1, return 2
            "jne  BaseCase;"                        
            "mov  EAX, 2;"                         // Sets return register to 2 if statement is above is true
            "jmp  GeometEnd;"
        "BaseCase:"
            "mov  DWORD PTR [EBP - 8], 0;"         // Initialize for loop counter (int i = 0)
        "ForLoop:"
            "mov  EAX, DWORD PTR [EBP + 8];"       // Move input parameter into a register
            "sub  EAX, 2;"                         // For loop should only run (input - 2) times according to formula
            "cmp  DWORD PTR [EBP - 8], EAX;"       // Text Expression of for loop (i < input - 2)
            "jge  EndOfLoop;"                       
            "mov  EDX, DWORD PTR [EBP - 4];"       // Move power variable into a register for calculations
            "mov  EAX, EDX;"                       // Different way of doing power *= 12 for each loop iteration (I didn't want to deal with mul)
            "add  EAX, EAX;"
            "add  EAX, EDX;"                       // EAX = 12 * 3
            "sal  EAX, 2;"                         // Shift EAX register left by 2 bits, turns 36 into 144
                                                   // 00100100 = 36 --> 10010000 = 144
            "mov  DWORD PTR [EBP - 4], EAX;"       // Places product back into power variable
            "add  DWORD PTR [EBP - 8], 1;"         // For loop Increment (i++)
            "jmp  ForLoop;"                        // Repeat until i >= input - 2
        "EndOfLoop:"
            "mov  EAX, DWORD PTR [EBP + 8];"       // Move parameter input into register
            "sub  EAX, 1;"                         // Input - 1, to be used for formula
            "push EAX;"                            // Push Input - 1 onto the stack to be used as a parameter for the next recursive call
            "call geomet;"                         // When function call is done, return value is in EAX
            "add  ESP, 8;"                         // 'Pop' everything from recursive call
            "mov  EDX, DWORD PTR [EBP - 4];"       // Move product of (12^n - 2) into EDX       
            "add  EDX, EDX;"                       // Add according to formula: (2 * 12^n - 2)
            "add  EAX, EDX;"                       // Add according to formula: geomet(input - 1) + (2 * 12^n - 2)
        "GeometEnd:"
            "mov esp, ebp;"                        // Function Epilogue
            "pop ebp;"
            "ret;"
    
        "end:"                                     // A label for the code to go so it doesn't run the function when
                                                   //       it's not supposed to
        :"=a" (series)
        :"a" (input)
    );

    cout << "f(" << input << ") = " << series << endl;
    return 0;
}

// Was that too many comments? I'm legitimately not sure