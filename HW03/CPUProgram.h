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
    CPUProgram(string name); //get file name and call readfile func.
    
   /* getLine function takes an integer as the parameter and returns a string 
    that contains the program line that corresponds to the integer.*/
    const string getLine(const int &number) const { return data[number]; }    
    const int getSizeOfData() const { return size; } 
    const string getFileName(){ return fileName; }
    const bool getFileIsOpen() const { return fileIsOpen; }
    const string getData(const int &number) const { return data[number]; }
    
private:  
    const string editSpacesAndTabs(string line) const;
    const void uppercaseConverter(string &buffer) const;
    /*ReadFile function takes a string file name as a parameter, reads the  
    program file and stores all the program instructions. */
    const void ReadFile(const string &FileName);
    
    string fileName; //name of file will open
    vector <string> data; //all of informations based on file
    int size = 0; //size of data which number of lines of file
    bool fileIsOpen = true; 
};

#endif
