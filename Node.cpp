#include "Node.h"
using namespace std;

Node::Node(){

}

Node::~Node(){
    
}

bool Node::canAddResistor(int rIndex){
    if (numRes == MAX_RESISTORS_PER_NODE){
        cout << "Error: node is full" << endl;
        return false;
    }
    return true;
}

void Node::addResistor(int rIndex){
    resIDArray[numRes] = rIndex;
    numRes++;
}

void Node::print(int nodeIndex){
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;
}