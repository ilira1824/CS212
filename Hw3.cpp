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
        "push EAX;"
        "fld DWORD PTR [ESP - 8];"
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
            "fsin;"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "cosine:"
            "fcos;"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "tangent:"
            "fsincos;"
            "fdiv st(1), st(0);"            // st(0) = cos      st(1) = sin
            "fstp DWORD PTR [ESP + 4];"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "area:"                             // PI r^2
            "fmul st(0), st(0);"
            "fldpi;"
            "fmul st(0), st(1);"
            "fstp DWORD PTR [ESP];"
            "jmp end;"
        "volume:"                           // 4/3 Pi r^3
            "fmul st(0), st(0);"
            "fmul st(0), st(0);"            // r^3
            "jmp end;"
        "log2:"
        "ln:"
        "log10:"
        "end:"
            "mov EAX, DWORD PTR [ESP];"

        :"=a" (result)
        :"a" (param), "b" (operation)
    );

    cout << result << endl;

    return 0;
}