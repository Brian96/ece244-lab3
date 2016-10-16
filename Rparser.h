#ifndef RPARSER_H
#define RPARSER_H

#include "Resistor.h"
#include "Node.h"

class Parser{
private:
    int maxNodeNumber = 0;
    int maxResistors = 0;
    int numResistors = 0;
    Node *nodeList;
    Resistor *resisList;
    void setMax(std::string line);
    void insertR(std::string line);
    void modifyR(std::string line);
    void printR(std::string line);
    void printNode(std::string line);
    void deleteR(std::string line);
public:
    Parser();
    ~Parser();
    void start();
};

#endif	/* RPARSER_H */
