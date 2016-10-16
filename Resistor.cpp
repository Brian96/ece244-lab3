#include "Resistor.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Resistor::Resistor(){}

Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]){
    this -> index = rIndex_;
    this -> resistance = resistance_;
    this -> name = name_;
    this -> endpointNodeIDs[0] = endpoints_[0];
    this -> endpointNodeIDs[1] = endpoints_[1];
}

Resistor::~Resistor(){
    
}

/*Resistor& Resistor::operator=(const Resistor &re){
    this -> index = re.index;
    this -> resistance = re.resistance;
    this -> name = re.name;
    this -> endpointNodeIDs[0] = re.endpointNodeIDs[0];
    this -> endpointNodeIDs[1] = re.endpointNodeIDs[1];
    return *this;
}
*/
string Resistor::getName() const{
    return this -> name;
}

double Resistor::getResistance() const{
    return this -> resistance;
}

void Resistor::setResistance (double resistance_){
    this -> resistance = resistance_;
}

int Resistor::getFirstEnd() const{
    return endpointNodeIDs[0];
}

int Resistor::getSecondEnd() const{
    return endpointNodeIDs[1];
}
ostream& operator<<(ostream& out,const Resistor& re){
    out << setw(20) << left << re.name;
    out << " ";
    out << setw(8) << right << setprecision(2) << fixed << re.resistance;
    out << " Ohms ";
    out << re.endpointNodeIDs[0] << " -> " << re.endpointNodeIDs[1];
    return out;
}