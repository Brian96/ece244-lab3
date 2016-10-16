#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

class Resistor{
private:
    double resistance; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    int index;
public:
    Resistor();
    Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2]);
    
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects

    ~Resistor();
    //Resistor &operator=(const Resistor &re);

    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    void setResistance (double resistance_);
    
    int getFirstEnd() const;
    int getSecondEnd() const;
    // you *may* create either of the below to print your resistor
    friend ostream& operator<<(ostream&,const Resistor&);
};

ostream& operator<<(ostream& out,const Resistor& re);

#endif	/* RESISTOR_H */
