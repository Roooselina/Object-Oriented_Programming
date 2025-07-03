// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <stdexcept>
using namespace std;

//=========================================================
// 1. C++ program to demonstate the use of try, catch, and throw 
// in exception handling
//=========================================================
int main()
{
    // try block
    try {
        int numerator = 10;
        int denominator = 0;
        int quotient;

        // check if denominator is 0 then throw runtime
        // error.
        if (denominator == 0) {
            throw runtime_error(
                "Division by zero not allowed!");
        }

        // calculate result if no exception occurs
        quotient = numerator / denominator;
        //[printing result after division
        cout << "Result after division: " << quotient << endl;
    }
    // catch block to catch the thrown exception
    catch (const exception& e) {
        // print the exception
        cout << "Exception " << e.what() << endl;
    }

    return 0;
}

//=========================================================
// 2. C++ program to demonstate the use of try,catch and throw 
// in exception handling
//=========================================================
int main()
{
    int x = -1;

    // Some code
    cout << "Before try \n";

    // try block
    try {
        cout << "Inside try \n";
        if (x < 0) {
            // throwing an exception
            throw x;
            cout << "After throw (Never executed) \n";
        }
    }

    // catch block
    catch (int x) {
        cout << "Exception Caught \n";
    }

    cout << "After catch (Will be executed) \n";
    return 0;
}

//=========================================================
// 3. C++ program to demonstate the use of catch all
// in exception handling.
//=========================================================
int main()
{
    // try block
    try {

        // throw
        throw 10;
    }

    // catch block
    catch (char* excp) {
        cout << "Caught " << excp;
    }

    // catch all
    catch (...) {
        cout << "Default Exception\n";
    }
    return 0;
}

//=========================================================
// 4. Conversion doesn't happen for primitive types.
// in exception handling.
//=========================================================
int main()
{
    try {
        throw 'a';
    }
    catch (int x) {
        cout << "Caught " << x;
    }
    catch (...) {
        cout << "Default Exception\n";
    }
    return 0;
}

//=========================================================
// 5. If an exception is thrown and not caught anywhere, 
// the program terminates abnormally in exception handling
//=========================================================
int main()
{
    try {
        throw 'a';
    }
    catch (int x) {
        cout << "Caught ";
    }
    return 0;
}

//=========================================================
// C++ program to demonstrate try/catch blocks can be nested
// in C++
//=========================================================
int main()
{
    // nesting of try/catch
    try {
        try {
            throw 20;
        }
        catch (int n) {
            cout << "Handle Partially ";
            throw; // Re-throwing an exception
        }
    }
    catch (int n) {
        cout << "Handle remaining ";
    }
    return 0;
}

//=========================================================
// Define a class named Test
//=========================================================
class Test {
public:
    // Constructor of Test
    Test() { cout << "Constructor of Test " << endl; }
    // Destructor of Test
    ~Test() { cout << "Destructor of Test " << endl; }
};

int main()
{
    try {
        // Create an object of class Test
        Test t1;

        // Throw an integer exception with value 10
        throw 10;
    }
    catch (int i) {
        // Catch and handle the integer exception
        cout << "Caught " << i << endl;
    }
}
// 예외 처리 = 대안 제시
// try: 예외 발생 가능성 영역
// catch: 예외에 대한 대안
// throw: 각 예외에 대한 flag return

// throw 실행 이후, 각 오류에 맞는  catch 실행