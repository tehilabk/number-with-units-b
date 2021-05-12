
#include <iomanip>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;


int main() {

    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    int choosen;
    cout<<"Welcome!"<<endl;
    string src;
    string dst;
    double amount1;
    double amount2;




    while (true) {
        cout
                << "To print press 1:\nTo convert units press 2:\n Enter 0 for Exit\n"
                << endl;
    
        cin >> choosen;
        
        switch (choosen) {
            case 0:
                cout << "Exit" << endl;
                exit(0);
            case 1:
                NumberWithUnits::printer();
                break;
            case 2:
                cout << "Enter the first unit" << endl;
                cin >> src;
                cout << "Enter the secund unit" << endl;
                cin >> dst;
                cout << "how much units to convert?" << endl;

                cin >> amount1;
               
                try {
                    cout << amount1 << '[' << src << ']' << '=' << setprecision(5)
                         << NumberWithUnits::convertToFirst(src, dst, amount1)<< '['
                         << dst << ']'<< "\n" <<endl;
                    break;
                } catch (...) {
                    cout << "wrong input, please try again!" << endl;
                    break;
                }
            default:
                cout << "wrong input, please try again!"<<endl;
                break;
        }
    }
}