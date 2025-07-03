#include <iostream>
using namespace std;

void doubleupByValue(int a) {
    a *= 2;
}

void doubleupByReference(int& a) {
    a *= 2;
}

void doubleupByPointer(int* a) {
    *a *= 2;
}

int main() {
    int method;
    int a = 10;  int pa = a;
    int b = 10;  int& pb = b;
    int c = 10;  int* pc = &c;

    cout << "This code is meant to demonstrate the concept of pointers and references." << endl;

    while (true) {
        cout << "Which method do you want to test out? 1 for values, 2 for references, 3 for pointers" << endl;
        cin >> method;

        switch (method) {
        case 1:
            cout << "Creating another copy of your parameter" << endl;
            doubleupByValue(pa);
            cout << a << " vs. " << pa << endl;
            cout << &a << " vs. " << &pa << endl;
            cout << "Neither is doubled up since the parameter value is internally handled!" << endl;
            break;

        case 2:
            cout << "Duplicating your parameter (i.e. assigning the second name)" << endl;
            doubleupByReference(pb);
            cout << b << " vs. " << pb << endl;
            cout << &b << " vs. " << &pb << endl;
            cout << "Both are doubled up!" << endl;
            break;

        case 3:
            cout << "Referencing the parameter via its address" << endl;
            doubleupByPointer(pc);
            cout << "c = " << c << " vs. " << "pc = " << pc << endl;
            cout << "&c = " << &c << " vs. " << "*pc = " << *pc << " vs. " << "&pc = " << &pc << endl;
            cout << "The parameter's address is passed on to the function!" << endl;
            cout << "btw" << endl;
            cout << "No. of bytes of c = " << sizeof(*pc) << "\nNo. of bytes of c's address = " << sizeof(pc) << endl;
            break;

        default:
            cout << "A wrong option!" << endl;
        }
    }
    return 0;
}
