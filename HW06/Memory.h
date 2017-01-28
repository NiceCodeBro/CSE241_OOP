#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>  
#include "CPU.h"
using namespace std;

class Memory
{
    
public:
    Memory();
    Memory(const int &opt) ;
    const int getMem(const int &index) const { return memory[index]; }
    const void setMem(const int &index, const int number) { memory[index] = number; }
    const void printAll() const; //print all memory members value
    const void setOption(const int &number){ option = number;}
    const int getMemSize() const { return memorySize; }
private:
    unsigned int memory[50]; // memory keep number that situate on adress 
    int option;
    int memorySize ; 
};

#endif /* MEMORY_H */

