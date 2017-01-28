#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>  
class Instruction //using class such as struct
{
public:
    Instruction(); 
    bool MovAddSubProb1; //if true mean that MovAddSub reg, reg
    bool MovAddSubProb2; //if true mean that MovAddSub reg, constant
    int MovAddSubRegNum1, MovAddSubRegNum2; // if need, registerNumber2 using  
    int MovAddSubConst ;

    bool prnProb1 ; //if true mean that PRN reg
    bool prnProb2 ; //if true mean that PRN constant 
    int prnRegNum1;
    int prnConst;

    bool jmpProb1 ; //if true mean that JMP reg, lineadress
    bool jmpProb2 ; //if true mean that JMP lineadress
    int jmpRegNum1;
    int jmpLineAdress;
};

#endif
