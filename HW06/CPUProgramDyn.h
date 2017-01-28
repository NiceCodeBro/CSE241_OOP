#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
using namespace std;
namespace CPUProgramNamespace
{
	class CPUProgramDyn
	{
	public:
		CPUProgramDyn( );
		CPUProgramDyn(const int opt);
		CPUProgramDyn(string name); //get file name and call readfile func.
		CPUProgramDyn(const CPUProgramDyn &CPUProgram);

		~CPUProgramDyn( ){ delete []data; }
		/*ReadFile function takes a string file name as a parameter, reads the 
		program file and stores all the program instructions.*/
		const void ReadFile(const string FileName);
		
		/* getLine function takes an integer as the parameter and returns a string 
		that contains the program line that corresponds to the integer.*/
		const string getLine(const int number) const { return data[number]; }    
		const int size( ) const { return totalSize; } 
		const string getFileName( ){ return fileName; }
		const bool getFileIsOpen( ) const { return fileIsOpen; }
		const string getData(const int number) const { return data[number]; } 
		const int getCapacity( ) const {return capacity; } ///
		const void setCapacity(const int newCapacity ) { capacity = newCapacity; }
		const void setSize(const int number) { totalSize = number; } 
		const void setOption(const int number){ option = number;} 
		const void setData(const string var); 
		const void delLastData( );          
		
		//assignment operator overloading
		const void operator =(const CPUProgramDyn &var); 
		//operator overloading functions
		const CPUProgramDyn operator -- (int ); //postfix version, that delete the last line of the program.
		const void operator -- ( ); //prefix version, that delete the last line of the program.
		//takes an integer and works like the getLine function. It returns the program line as a string.
		const string operator [](const int number) const;
		//takes two integers and returns a new program that contains the instructions between the given integers.
		const CPUProgramDyn operator ( ) (const int number1, const int number2) const; 
		
		//It returns a new CPUProgram that has the original CPUProgram with appended last line from the parameter string.
		const CPUProgramDyn operator + (const string newInstruction) const; 
		//Operator+ that takes two programs and returns a new program that appends the second programs to the first one
		const CPUProgramDyn operator + (const CPUProgramDyn &var1) const;
		//takes an instruction line as a string and appends the instruction to the end of the program.
		const void operator += (const string newInstruction);
		//comparison overloading functions,, compare the number of lines of the programs.
		const bool operator == (const CPUProgramDyn &var) const; 
		const bool operator > ( const CPUProgramDyn &var) const; 
		const bool operator < ( const CPUProgramDyn &var) const; 
		const bool operator <= (const CPUProgramDyn &var) const; 
		const bool operator >= (const CPUProgramDyn &var) const;
		const bool operator != (const CPUProgramDyn &var) const;
		
		//that prints the program
		friend ostream& operator <<(ostream& outputStream, const CPUProgramDyn &var);


	private:  
		const string editSpacesAndTabs(string line) const;
		const void uppercaseConverter(string &buffer) const;
		string fileName; //name of file will open
		string *data; //all of informations based on file
		bool fileIsOpen; 
		int option;
		int capacity; //capacity of data
		int totalSize; //size of data which number of lines of file

	};
}
#endif
