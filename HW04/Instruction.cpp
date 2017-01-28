#include "Instruction.h"

using namespace std;
//Constructure of Instruction class
Instruction::Instruction()
{
    movProb1 = false; //if true mean that MOV reg, reg
    movProb2 = false; //if true mean that MOV reg, constant
    movProb3 = false; //if true mean that MOV reg, adress
    movProb4 = false; //if true mean that MOV adress, reg
    movProb5 = false; //if true mean that MOV adress, constant
    
    
    addSubProb1 = false; //if true mean that Add&Sub reg, reg
    addSubProb2 = false; //if true mean that Add&Sub reg, constant
    addSubProb3 = false; //if true mean that Add&Sub reg, adress

    prnProb1 = false; //if true mean that PRN reg
    prnProb2 = false; //if true mean that PRN constant 
    prnProb3 = false; //if true mean that PRN adress

    jmpProb1 = false; //if true mean that JMP reg, lineadress
    jmpProb2 = false; //if true mean that JMP lineadress
    
    jpnProb1 = false; //if true mean that JPN reg, lineadress
}
