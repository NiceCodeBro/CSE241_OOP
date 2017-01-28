#ifndef CPU_H
#define CPU_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include"CPUProgram.h"
#include"Instruction.h"
#include "Memory.h"
class Memory;
using namespace std;
class CPU
{
public:
    CPU();
    CPU(const int number);
    //getters for Program Counter and Registers
    const int getPC() const { return PC; }
    const int getRegister(const int &num) const { return R[num]; }
    const void setRegister(const int &num, const int &number) { R[num] = number; }
    const void setPC (const int &number) { PC = number; }
    const string getMessage(const int &index) const { return messages[index]; }
    const vector<string> getMessages() const { return messages; }
    const void setOption(const int &number) { option = number; }
    const int getOption() { return option; }
    /*function takes a string that contains an instruction line, executes it 
    and advances the PC accordingly */
    const void execute(const string &instLine, Memory &myMemory );
    const bool halted() const; //check that if last instruction is "HLT" or not
    const int stringToInteger(const string &arg) ;  //convert string to integer
    //control func. of negative assing to Memory element
    const int logicErrorCase(const int &number);
    const void print() const; //print PC and registers
private: 
    const int movControl(string body, Instruction &inst) ;
    const int addSubControl(string body, Instruction &inst) ;
    const int prnControl(string body, Instruction &inst) ;
    const int jmpControl(string body, Instruction &inst) ;
    const int jpnControl(string body, Instruction &inst) ;
    //parsing function with delimeters
    const int cStrTok(string &strng, string &buffer, const char &delim) const;
    const string editSpacesAndTabs(string line) const;
    const bool stringConvToInt(const string &myString, int &number);
    const string intToString ( const int &num ) const;
    const void printErrorOrMessages () const;
    int R[5]; // 5 is number of registers, R[0] = R1 , R[1]=R2 ...
    int PC ; // Program counter
    string instruction; //instruction will check in halted function in main
    bool END = false; //if true, all process will stop
    vector <string> error; //if any error exist, this vector will use
    vector <string> messages; //if any PRN instruction exist, this vector will use
    int option; //command line option.  it value must be 1 or 0.
};

#endif
