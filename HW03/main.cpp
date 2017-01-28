/*
	131044023 
	MUHAMMED SELIM DURSUN
	CSE241 - HW#03


*/

#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
//header files
#include "CPUProgram.h"
#include "Instruction.h"
#include "CPU.h"
using namespace std;

int main(int argc, char** argv) 
{   
    if(argc != 3)
    {
        cout << "Missing or to much argument..." << endl;
        return -1;
    }
    CPUProgram myProg( argv[1] );  
    CPU myCPU;

    myCPU.setOption(myCPU.stringToInteger(argv[2])) ;
    /*if option command not equal 1 or 0*/
    if(myCPU.getOption() == -1 || !(myCPU.getOption() == 0 || myCPU.getOption() == 1) )
    {
        cout << "Invalid option !" << endl;
        return -1;
    }
    //if file is open
    if(myProg.getFileIsOpen())
    {
        while(!myCPU.halted()) //if instruction not equal HLT, go on
        { 
            string instruction = myProg.getLine(myCPU.getPC());
            myCPU.execute(instruction);
        }
    }
    else //if not open, exit
        return -1;
    
    return 0;
}
