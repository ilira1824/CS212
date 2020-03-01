#include <iostream>

using namespace std;

int main() {
    char operation;
    float param, result;

    cout << "Which operation would you like to perform?\n";
    cout << "(s) sine, (c) cosine, (t) tangent\n";
    cout << "(a) area of a circle, (v) volume of a sphere\n";
    cout << "(g) log_2, (n) ln, (l) log_10\n";

    cin >> operation;

    switch(operation) {
        case 'a':
            cout << "Enter radius: ";
            cin >> param;
            break;
        case 'v':
            cout << "Enter radius: ";
            cin >> param;
            break;
        default:
            cout << "Enter input: ";
            cin >> param;
            break;
    }


    asm (
        "cmp EBX, 97;" // area case
        "je area;"
        "cmp EBX, 115;" // sine case
        "je sine;"
        "cmp EBX, 99;" // cosine case
        "je cosine;"
        "cmp EBX, 116;" // tangent case
        "je tangent;"
        "cmp EBX, 118;" // volume case
        "je volume;"
        "cmp EBX, 103;" // log 2 case
        "je log2;"
        "cmp EBX, 110;" // ln case
        "je ln;"
        "cmp EBX, 108;" // log 10 case
        "je log10;"

        "sine:"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fsin;"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "cosine:"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fcos;"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "tangent:"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fsincos;"
            "fdiv st(1), st(0);"            // st(0) = cos      st(1) = sin
            "fstp DWORD PTR [ESP + 4];"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "area:"                             // PI r^2
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fmul st(0), st(0);"
            "fldpi;"
            "fmul st(0), st(1);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "volume:"                           // 4/3 Pi r^3
            "mov ECX, 3;"
            "mov EDX, 4;"
            "push ECX;"
            "fld DWORD PTR [ESP];"
            "push EDX;"
            "fld DWORD PTR [ESP];"          // st(2) = input
            "fdiv st(0), st(1);"            // st(0) = 4/3
            "fldpi;"
            "fmul st(0), st(1);"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fmul st(0), st(0);"
            "fld DWORD PTR [ESP];"
            "fmul st(0), st(1);"
            "fmul st(0), st(2);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "log2:"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fld1;"
            "fld1;"
            "fadd st(0), st(0);"
            "fyl2x;"                        // st(0) = log2(2)
            "fld1;"
            "fld DWORD PTR [ESP];"
            "fyl2x;"                        // st(0) = log2(input)          st(1) = log2(2)
            "fdivp st(1), st(0);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "ln:"
            "push EAX;"
            "fld DWORD PTR [ESP];"
            "fld1;"
            "fld DWORD PTR [ESP];"
            "fyl2x;"                        // st(0) = log2(input)
            "fldl2e;"                       // st(0) = log2(e)           st(1) = log2(input)
            "fdivp st(1), st(0);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "log10:"
            "push EAX;"
            "fld DWORD PTR [ESP];" 
            "fld1;"                         // st(0) = 1
            "fld DWORD PTR [ESP];"
            "fyl2x;"                        // st(1) = 1 * log2(input)          st(0) = input
            "fldl2t;"                       // st(0) = log2(10)           st(1) = input          st(2) = log2(input)
            "fdiv st(0), st(1);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "end:"
            "mov EAX, DWORD PTR [ESP];"

        :"=a" (result)
        :"a" (param), "b" (operation)
    );

    cout << result << endl;

    return 0;
}