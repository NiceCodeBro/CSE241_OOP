#include "Computer.h"
using namespace std;
Computer::Computer(const int opt)
{ 
    option = opt;
    getCPU().setOption(opt);
}
Computer::Computer(const CPU &var1, const CPUProgram &var2, const Memory &var3, const int &opt)
{
    setCPU(var1);
    setCPUProgram(var2);
    setMemory(var3);
    getCPU().setOption(opt);
    setOption(opt);
}

const void Computer::execute()
{
    //if file is open
    if(myCPUProgram.getFileIsOpen() )
    {
        while(!myCPU.halted() && IsHLTexist() ) //if instruction not equal HLT, go on
        {   
            string instruction = myCPUProgram.getLine(myCPU.getPC());
            myCPU.execute(instruction, myMemory);        
        }      
    }
    else
    {//if not open, exit
        exit(1);
    }
}
//check if hlt instruction is exist or not, if not exist exit program
const bool Computer::IsHLTexist() const
{
    if(myCPU.getPC() >= getCPUProgram().size())
    {
        cerr << "HLT instruction is not found. Program terminated. " << endl;
        exit(1);
    }
    else
        return true;
}