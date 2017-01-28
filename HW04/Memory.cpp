#include "Memory.h"
using namespace std;
//defaul constructure
Memory::Memory()
{
    memorySize= 50;
    for(int i = 0; i < 50; ++i)
        memory[i] = 0;   
}
Memory::Memory(const int &opt)
{
     memorySize= 50;
    for(int i = 0; i < 50; ++i)
        memory[i] = 0;
    setOption(opt);
}
//print all memory members value
const void Memory::printAll() const
{
    cout << "Memory Values:" << endl;
    for(int i = 0; i < 50; ++i)
    {
        cout << "[" <<  i << "]" << "->" << getMem(i) << endl; 
    }
    
}
