#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

namespace ariel {

    const double EPS = 0.001;
    class NumberWithUnits{

    private:
        double val;
        string type;

    public:
        NumberWithUnits(double val, const string &type);

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

        NumberWithUnits operator*(const double x) const;
        friend NumberWithUnits operator*(const double x, const NumberWithUnits& num);
       
        bool operator>(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;

        double static convertToFirst (const string &firstType, const string &secondType, const double val);
        void static printer ();
    };
}