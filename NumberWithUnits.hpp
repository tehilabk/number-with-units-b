#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

namespace ariel {
    class NumberWithUnits{

    private:
        double val;
        string type;

    public:
        NumberWithUnits(double val, string type);

        static void read_units(ifstream& file);

        friend ostream& operator<<(ostream& out, const NumberWithUnits& num);
        friend istream& operator>>(istream& in, NumberWithUnits& num);
       
        NumberWithUnits operator+();
        NumberWithUnits operator+(const NumberWithUnits& num);
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);

        NumberWithUnits operator-();
        NumberWithUnits operator-(const NumberWithUnits& num);
        NumberWithUnits& operator-=(const NumberWithUnits& num);

        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);

        NumberWithUnits operator*(const double x);
        friend NumberWithUnits operator*(const double x, NumberWithUnits& num);
       
        bool operator>(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;

    };
}