#include "CPUProgram.h"
using namespace std;

//CPUProgram default constructure
CPUProgram::CPUProgram()
{
    setSize(0);
    fileIsOpen = true; 
};

CPUProgram::CPUProgram(string name)//:fileName(name)
{
    fileName = name;
    setSize(0);
    fileIsOpen = true; 
    ReadFile(fileName);    
}
//////////////////////////////////
//Operator overloading

//Operator[] that takes an integer and works like the getLine function. 
//It returns the program line as a string.
const string CPUProgram::operator [](const int &number) const
{
    if(number >= 0 && number < this->size())
        return data[number];
    else
    {
        cerr<<"[] operator range error."<<endl;
        return "";
    }
}
const void CPUProgram::setData(const string &var) 
{
    data.push_back(var);
    setSize(size()+1);
}
const void CPUProgram::delLastData() 
{
    data.pop_back();
    setSize(size()-1);
}
//comparison overloading functions,, compare the number of lines of the programs.
const bool CPUProgram::operator ==(const CPUProgram &var) const
{
    return (this->size() == var.size());
}
const bool CPUProgram::operator > (const CPUProgram &var) const 
{
   return (this->size() > var.size());
}
const bool CPUProgram::operator < (const CPUProgram &var) const
{
    return (this->size() < var.size());
}
const bool CPUProgram::operator <=(const CPUProgram &var) const
{
    return (this->size() <= var.size());
}
const bool CPUProgram::operator >=(const CPUProgram &var) const 
{
    return (this->size() >= var.size());
}
const bool CPUProgram::operator != (const CPUProgram &var)const     
{
    return (this->size() != var.size());
}
//that prints the program
ostream& operator <<(ostream& outputStream, const CPUProgram &var)
{
    for(int i = 0; i < var.getDataVector().size(); ++i)
    {
       if(i < var.getDataVector().size()-1)
            outputStream << var.getData(i)<<endl;
       else
            outputStream << var.getData(i);
    }
    return outputStream;
}
//takes two integers and returns a new program that contains the instructions between the given integers.
const CPUProgram CPUProgram::operator () (const int number1, const int number2) const
{
    CPUProgram newCPUProg;    
    if(number1 > number2 || number1<0 || number2<0) //error check
    {
        cerr << "() operator range error."<<endl;
        return newCPUProg;
    }
    for(int i = number1; i <= number2; ++i)
        newCPUProg.setData( getData( i ) );
    
    newCPUProg.setSize(number2 - number1 + 1);
    
    return newCPUProg;
}
const CPUProgram CPUProgram::operator -- (int) //postfix version, that delete the last line of the program.
{
	CPUProgram temp;
	for(int i=0; i<this->getDataVector().size(); ++i)
	{
		temp.setData(this->getData(i));	
	}
    delLastData();

    return temp;
}
const void CPUProgram::operator -- () //prefix version, that delete the last line of the program.
{   
    delLastData();
}
//It returns a new CPUProgram that has the original CPUProgram with appended last line from the parameter string.
const CPUProgram CPUProgram::operator +( const string &newInstruction) const
{
	CPUProgram prog;
	if(newInstruction[0]=='\0') 
	{
		cerr<<"You can not append empty string."<<endl;
		return prog;
	}
    
    for(int i = 0; i < this->getDataVector().size(); ++i)
        prog.setData( this->getData( i ) ) ;
    
    prog.setData( newInstruction ) ;  
    prog.setSize(this->getDataVector().size() + 1 );

    return prog;
}
//takes an instruction line as a string and appends the instruction to the end of the program.
const void CPUProgram::operator +=( const string &newInstruction)
{
	if(newInstruction[0]=='\0') 
	{
		cerr << "You can not append empty string." << endl;
	}
	else
    	this->setData( newInstruction );    
 
}   
//Operator+ that takes two programs and returns a new program that appends the second programs to the first one
const CPUProgram CPUProgram::operator +(const CPUProgram &var1) const
{ 
    CPUProgram prog;
    for(int i = 0; i < this->getDataVector().size(); ++i)
        prog.setData( this->getData( i ) ) ;
    
    for(int j = 0; j < var1.getDataVector().size(); ++j)
        prog.setData( var1.getData( j ) ) ;
    
    prog.setSize(this->getDataVector().size() + var1.getDataVector().size() );
    
    return prog;
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
                totalSize++; //total line of file
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
