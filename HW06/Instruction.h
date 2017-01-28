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
    bool movProb1 ; //if true mean that MOV reg, reg
    bool movProb2 ; //if true mean that MOV reg, constant
    bool movProb3 ; //if true mean that MOV reg, adress
    bool movProb4 ; //if true mean that MOV adress, reg
    bool movProb5 ; //if true mean that MOV adress, constant
    
    bool addSubProb1 ; //if true mean that Add&Sub reg, reg
    bool addSubProb2 ; //if true mean that Add&Sub reg, constant
    bool addSubProb3 ; //if true mean that Add&Sub reg, adress

    bool prnProb1 ; //if true mean that PRN reg
    bool prnProb2 ; //if true mean that PRN constant 
    bool prnProb3 ; //if true mean that PRN adress

    bool jmpProb1 ; //if true mean that JMP reg, lineadress
    bool jmpProb2 ; //if true mean that JMP lineadress
    
    bool jpnProb1; //if true mean that JPN reg, lineadress
    
    int registerNumber1, registerNumber2 ; // if need, registerNumber2 using 
    int adressNumber ;
    int constant ;
    int lineAdress;
};

#endif
