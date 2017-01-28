#include "CPUProgram.h"
using namespace std;

//CPUProgram default constructure
CPUProgram::CPUProgram(string name):fileName(name)
{
    fileName = name;
    ReadFile(fileName);
}
//if any case lower case in file, convert to upper case
const void CPUProgram::uppercaseConverter(string &buffer) const
{
    for(int i=0; i<(buffer).size();++i)
    {
        if(buffer[i] >= 'a' && buffer[i] <= 'z')
            buffer[i] -= 'a' - 'A';
    }
}
/*
	ReadFile function takes a string file name as a parameter, reads the 
	program file and stores all the program instructions.
*/
const void CPUProgram::ReadFile(const string &FileName)
{
    fstream inp;   
    string buffer;
    inp.open(FileName);
    
    if (!inp.is_open()){
        cout << "Can't open the file" << endl;
        fileIsOpen = false;
    }
    else if(fileIsOpen)
    {
        while(!inp.eof()){
            getline(inp, buffer);
            buffer = editSpacesAndTabs(buffer); //string simplification
            uppercaseConverter(buffer);

            if(!inp.eof())
            {
                data.push_back(buffer);
                size++; //total line of file
            }
        }
        inp.close();
    }
}

//string simplification as per following conditions
const string CPUProgram::editSpacesAndTabs(string line) const
{   
    int i, number;
    string buffer;
    
    //deleting head spaces
    for(int i = 0; i < line.size(); ++i)
    {
        if(line[i]>='A' && line[i]<='z')
        {
            line = &line[i];
            i = line.size();
        }
    }
    //if string have '\t', exchange with one space
    for(i=0; i< line.size(); ++i)
    {
        if(line[i] == '\t')
        {
            line[i]=' ';
        }
    }
    //if string have ';' character, erase after ';'
    number = line.find(";");
    if(number != -1) line.erase(number);
    
    // if string has double space, changing with one space
    number = line.find("  ");
    while(number!=-1)
    {
        line.replace(number,2," ");
        number = line.find("  ");
    }
    
    //deleting space if space after comma
    number = line.find(", ");
    while(number!=-1)
    {
        line.replace(number,2,",");
        number = line.find(", ");
    }
    //deleting space if space before comma
    number = line.find(" ,");
    while(number!=-1)
    {
        line.replace(number,2,",");
        number = line.find(" ,");
    }
    
    //deleting space at the end of string if exist
    if(line[line.size()-1] != ' ')
    {
        line += ' ';
    }
        
    return line;
}
