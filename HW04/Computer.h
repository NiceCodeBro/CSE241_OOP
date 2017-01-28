#ifndef COMPUTER_H
#define COMPUTER_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>  
#include "CPUProgram.h"
#include "CPU.h"
//#include "Memory.h"
//#include "Instruction.h"
using namespace std;
class Computer
{
public:
    Computer() { option = 0; }
    Computer(const int opt);
    Computer(const CPU &var1, const CPUProgram &var2, const Memory &var3, const int &opt);
    
    CPU getCPU() const { return myCPU; }
    CPUProgram getCPUProgram() const { return myCPUProgram; }
    Memory getMemory() const { return myMemory; }
    const int getOption() const { return option;  }
    const void setCPU(const CPU &var1)  { myCPU = var1; }
    const void setCPUProgram(const CPUProgram &var2)  { myCPUProgram = var2;   }
    const void setMemory(const Memory &var3)  { myMemory = var3;  }
    const void setOption(const int &var4)  { option = var4;  }
    const void execute();
    const bool IsHLTexist( ) const;
private:
    CPU myCPU;
    CPUProgram myCPUProgram;
    Memory myMemory;
    int option;
};
#endif /* COMPUTER_H */

