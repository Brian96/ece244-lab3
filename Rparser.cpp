#include "Rparser.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Parser::Parser(){
    nodeList = NULL;
    resisList = NULL;
    maxNodeNumber = 0;
    maxResistors = 0;
    numResistors = 0;
}

Parser::~Parser(){
    if (nodeList != NULL)
        delete [] nodeList;
    if (resisList != NULL)
        delete [] resisList;
}

void Parser::start(){
    string line, cmd;
    cout << "> ";
    getline (cin, line);
    while (!cin.eof()) {
        stringstream ss (line);
        ss >> cmd;
        if (cmd == "maxVal") { //parse an maxVal command
            setMax(line);
        }
        else if (cmd == "insertR") { //parse an insert command
            insertR(line);
        }
        else if (cmd == "modifyR") {    //parse a modify command
            modifyR(line);
        }
        else if (cmd == "printR"){  //parse a print command
            printR(line);
        }
        else if (cmd == "printNode"){   //parse a printNode command
            printNode(line);
        }
        else if (cmd == "deleteR"){ //parse a delete command
            deleteR(line);
        }
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
}

void Parser::setMax(string line){
    stringstream ss(line);
    string cmd;
    int maxN, maxR;
    ss >> cmd;
    ss >> maxN;
    ss >> maxR;
    if (maxN <= 0 || maxR <= 0){
        cout << "Error: maxVal arguments must be greater than 0" << endl;
        return; //when trying to set either maxR or maxN to 0 or less than 0
    }
    if (maxResistors > 0 || maxNodeNumber > 0){
        delete [] nodeList;
        delete [] resisList;
    }
    nodeList = new Node[maxN+1];
    resisList = new Resistor[maxR];
    maxNodeNumber = maxN;
    maxResistors = maxR;
    numResistors = 0;
    cout << "New network: max node number is " << maxN << "; max resistors is " << maxR << endl;
}

void Parser::insertR(string line){
    stringstream ss(line);
    string cmd, name;
    double re;
    int end1, end2;
    ss >> cmd;
    ss >> name;
    ss >> re;
    ss >> end1;
    ss >> end2;
    if (end1 > maxNodeNumber || end1 < 0){
        cout << "Error: node " << end1 << " is out of permitted range 0-" << maxNodeNumber << endl;
        return;
    }
    if (end2 > maxNodeNumber || end2 < 0){
        cout << "Error: node " << end2 << " is out of permitted range 0-" << maxNodeNumber << endl;
        return;
    }
    if (numResistors == maxResistors){
        cout << "Error: resistor array is full" << endl;
        return;
    }
    if (!nodeList[end1].canAddResistor(numResistors)||!nodeList[end2].canAddResistor(numResistors)){
        return;
    }
    for (int i = 0; i < numResistors; i++){
        if (resisList[i].getName() == name){
            cout << "Error: resistor " << name << " already exists" << endl;
            return;
        }
    }
    if (end1 == end2){
        cout << "Error: both terminals of resistor connect to node " << end1 << endl;
        return;
    }
    cout << "Inserted: resistor " << name << " ";
    cout << setprecision(2) << fixed << re << " Ohms ";
    cout << end1 << " -> " << end2 << endl;
    int tem[2] = {end1, end2};
    //Resistor temp(numResistors,name,re,tem);
    resisList[numResistors] = Resistor(numResistors,name,re,tem);
    nodeList[end1].addResistor(numResistors);
    nodeList[end2].addResistor(numResistors);
    numResistors++;
    return;
}

void Parser::modifyR(string line){
    stringstream ss(line);
    string cmd, name;
    double re;
    ss >> cmd;
    ss >> name;
    ss >> re;
    for (int i = 0; i < numResistors; i++){
        if (resisList[i].getName() == name){
            double oldRes = resisList[i].getResistance();
            resisList[i].setResistance(re);
            cout << "Modified: resistor " << resisList[i].getName() << " from ";
            cout << setprecision(2) << fixed << oldRes << " Ohms to ";
            cout << setprecision(2) << fixed << resisList[i].getResistance() << " Ohms" << endl;
            return;
        }
    }
    cout << "Error: resistor " << name << " not found" << endl;
}

void Parser::printR(string line){
    stringstream ss(line);
    string cmd, name;
    ss >> cmd;
    ss >> name;
    if (name == "all"){
        cout << "Print:" << endl;
        for (int i = 0; i < numResistors; i++){
            cout << resisList[i] << endl;
        }
        return;
    }
    bool found = false;
    for (int i = 0; i < numResistors; i++){
        if (resisList[i].getName() == name){
            found = true;
            cout << "Print:" << endl;
            cout << resisList[i] << endl;
        }
    }
    if (!found){
        cout << "Error: resistor " << name << " not found" << endl;
    }
}

void Parser::printNode(string line){
    stringstream ss(line);
    stringstream sss(line);
    string cmd, name;
    int node;
    ss >> cmd;
    ss >> name;
    if (name == "all"){
        cout << "Print:" << endl;
        if (maxNodeNumber == 0) {
            return;
        }
        for (int i = 0; i <= maxNodeNumber; i++){
            nodeList[i].print(i);
            for (int j = 0; j < numResistors; j++){
                if (resisList[j].getFirstEnd() == i || resisList[j].getSecondEnd() == i){
                    cout << "  " << resisList[j] << endl;
                }
            }
        }
    }
    else {
        sss >> cmd;
        sss >> node;
        if (node > maxNodeNumber || node < 0){
            cout << "Error: node " << node << " is out of permitted range 0-" << maxNodeNumber << endl;
            return;
        }
        cout << "Print:" << endl;
        nodeList[node].print(node);
        for (int i = 0; i < numResistors; i++){
            if (resisList[i].getFirstEnd() == node || resisList[i].getSecondEnd() == node){
                cout << "  " << resisList[i] << endl;
            }
        }
    }
}

void Parser::deleteR(string line){
    string cmd, arg;
    stringstream ss(line);
    ss >> cmd;
    ss >> arg;
    if (arg == "all"){
        if (maxResistors > 0 || maxNodeNumber > 0){
            delete [] nodeList;
            delete [] resisList;
        }
        nodeList = new Node[maxNodeNumber+1];
        resisList = new Resistor[maxResistors];
        numResistors = 0;
    }
    cout << "Deleted: all resistors" << endl;
}
