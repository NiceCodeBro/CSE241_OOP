#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
using namespace std;
class CPUProgram
{
public:
    CPUProgram();
    CPUProgram(const int opt){ setOption(opt);  setSize(0); fileIsOpen=true;}
    CPUProgram(string name); //get file name and call readfile func.
   /* getLine function takes an integer as the parameter and returns a string 
    that contains the program line that corresponds to the integer.*/
    const string getLine(const int number) const { return data[number]; }    
    const int size() const { return totalSize; } 
    const string getFileName(){ return fileName; }
    const bool getFileIsOpen() const { return fileIsOpen; }
    const  vector <string>& getData() { return data; }
    const string getData(const int &number) const { return data[number]; }
    const void setSize(const int number) { totalSize = number; }
    /*ReadFile function takes a string file name as a parameter, reads the 
    program file and stores all the program instructions.*/
    const void ReadFile(const string &FileName);
    const void setOption(const int &number){ option = number;}
private:  
    const string editSpacesAndTabs(string line) const;
    const void uppercaseConverter(string &buffer) const;
    string fileName; //name of file will open
    vector <string> data; //all of informations based on file
    int totalSize ; //size of data which number of lines of file
    bool fileIsOpen ; 
    int option;
};

#endif
