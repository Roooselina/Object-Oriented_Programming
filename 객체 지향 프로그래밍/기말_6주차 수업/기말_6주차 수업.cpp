#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct TempData {
    int hour;
    double temperature;
};

// Function to write numbers to a file
void writeToFile() {
    ofstream os("number.txt");
    if (!os) {
        cerr << "Failed to open file" << endl;
        exit(1);
    }
    for (int i = 0; i < 100; i++) {
        os << i << " ";
    }
    cout << "Success!" << endl;
}

// Function to read numbers from a file
void readFile() {
    ifstream is("number.txt");
    if (!is) {
        cerr << "Failed to open file" << endl;
        exit(1);
    }
    int number;
    while (is >> number) {
        cout << number << " ";
    }
    cout << endl;
}

// Function to read temperature data from a file and display it
void readData() {
    ifstream is("temp.txt");
    if (!is) {
        cerr << "Failed to open file" << endl;
        exit(1);
    }
    vector<TempData> temps;
    int hour;
    double temperature;
    while (is >> hour >> temperature) {
        temps.push_back({ hour, temperature });
    }
    for (const auto& t : temps) {
        cout << t.hour << " hour: Temperature " << t.temperature << endl;
    }
}

// Function to enter and display an address
void enterAddress() {
    string address;
    cout << "Enter the address: ";
    if (!getline(cin, address)) {
        cerr << "Input error" << endl;
        return;
    }
    cout << "Hello, the resident who lives at " << address << endl;
}

// Function to demonstrate various number formats
void displayFormats() {
    cout << 30 << endl; // Default

    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << 30 << endl;

    cout.setf(ios::showbase);
    cout << 30 << endl;

    cout.setf(ios::uppercase);
    cout << 30 << endl;

    cout.setf(ios::dec | ios::showpoint);
    cout << 23.5 << endl;

    cout.setf(ios::scientific);
    cout << 23.5 << endl;

    cout.setf(ios::showpos);
    cout << 23.5 << endl;
}

int main() {
    // 디버깅 테스트
    cout << "1: \n";
    writeToFile();
    cout << "2: \n";
    readFile();
    cout << "3: \n";
    enterAddress();
    cout << "4: \n";
    displayFormats();
    cout << "5: \n";
    readData();

    return 0;
}
