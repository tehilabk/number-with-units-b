#include <iostream>
#include <fstream>
#include "NumberWithUnits.hpp"
#include <map>
using namespace std;

namespace ariel {

    map<string, map<string, double>> mapConvert; //<type,<type convert,val>

    NumberWithUnits::NumberWithUnits(double val, string type){
        try {
            mapConvert.at(type);
        }
        catch(const out_of_range) {
            throw invalid_argument("this type is unavailable");
        }
        this->val = val;
        this->type = type;
    }

       void updateTypes(string firstType,string secondType){
          for(auto &T : mapConvert[firstType]){
                double val = (mapConvert[T.first][firstType])*(mapConvert[firstType][secondType]);
                mapConvert[T.first][secondType] = val;
                mapConvert[secondType][T.first] = 1/val;
            }  
    }

    void NumberWithUnits::read_units(ifstream& file){
        double firstVal;
        string firstType;
        string equal;
        double secondVal;
        string secondType;
        if(!file){ //check if the file exists
            return;
        }
        while(file >> firstVal >> firstType >> equal >> secondVal >> secondType){
            mapConvert[firstType][secondType]=secondVal;
            mapConvert[secondType][firstType]=1/secondVal;
            updateTypes(firstType,secondType);
            updateTypes(secondType,firstType);
        }    
    }


    ostream& operator<<(ostream& out, const NumberWithUnits& num){
        return out<<num.val<<"["<<num.type<<"]";
    }

    istream& operator>>(istream& in, NumberWithUnits& num){
        string input;
        char c = ' ';
        while(in.get(c)){
            if(c==']'){
                break;}
            input+=c;    
        }
        input.erase(remove(input.begin(), input.end(), ' '),input.end());
        num.val = stod(input.substr(0,input.find('[')));
        num.type= (input.substr(input.find('[')+1,input.size()-input.find('[')-1));

        try {
            mapConvert.at(num.type);
        }
        catch(const out_of_range) {
            throw invalid_argument("this type is unavailable");
        }
        return in;
    }

    double convertToFirst (string firstType, string secondType, double val){
         try {
            mapConvert.at(firstType).at(secondType);
        }
        catch(const out_of_range) {
            throw invalid_argument("this type is unavailable");
        }
        return mapConvert[firstType][secondType]*val;  
    }


    NumberWithUnits NumberWithUnits::operator+(){
        return NumberWithUnits(this->val, this->type);
    }


    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& num) { 
    double numConvert = convertToFirst(num.type, this->type, num.val);
    return NumberWithUnits(this->val+numConvert, this->type);

    }
    
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& num) {
        this->val += convertToFirst(num.type, this->type, num.val);
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator++() {
        this->val++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        NumberWithUnits copy = NumberWithUnits(this->val, this->type);
        this->val++;
        return copy;
    }

    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(-this->val, this->type);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& num) {
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return NumberWithUnits(this->val-numConvert, this->type);
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& num) {
        this->val-=convertToFirst(num.type, this->type, num.val);
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator--() {
        this->val--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) {
        NumberWithUnits copy = NumberWithUnits(this->val, this->type);
        this->val--;
        return copy;    }


    NumberWithUnits NumberWithUnits::operator*(const double x) const{
        return NumberWithUnits(x*this->val, this->type);
    }

    NumberWithUnits operator*(const double x, const NumberWithUnits& num) {
        return num*x;
    }
  

    bool NumberWithUnits:: operator>(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return this->val > numConvert+EPS;

    }
    
    bool NumberWithUnits::operator<(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return this->val+EPS < numConvert;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return this->val >= numConvert+EPS || abs(this->val - numConvert)<EPS;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return this->val+EPS <= numConvert || abs(this->val - numConvert)<EPS;

    }

    bool NumberWithUnits::operator==(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return abs(this->val - numConvert)<EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits& num) const{
        double numConvert = convertToFirst(num.type, this->type, num.val);
        return !(abs(this->val - numConvert)<EPS);
    }

}