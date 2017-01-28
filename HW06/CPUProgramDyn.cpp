#include "CPUProgramDyn.h"
namespace CPUProgramNamespace
{
	//CPUProgram default constructure
	CPUProgramDyn::CPUProgramDyn()
	{
		setSize(0);
		fileIsOpen = true; 
		setCapacity(20);//capacity of data string array
		data = new string[capacity]; //allocating
	}
	
	CPUProgramDyn::CPUProgramDyn(const int opt){
		setOption(opt);  
		setSize(0); 
		fileIsOpen=true;
		setCapacity(20);//capacity of data string array
		data = new string[capacity];
	}

	CPUProgramDyn::CPUProgramDyn(const string name)
	{
		fileName = name;
		setSize(0);
		fileIsOpen = true; 
		setCapacity(20);//capacity of data string array
		data = new string[capacity];
		ReadFile(fileName);    
	}
	//copy constructor
	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn &CPUProgram)
	{
		setSize(CPUProgram.size());
		fileIsOpen = CPUProgram.fileIsOpen; 
		setCapacity(CPUProgram.getCapacity());
		data = new string[capacity];
		
		for(int i=0; i<CPUProgram.size(); ++i)
		    data[i] = CPUProgram.data[i];
	}

	//Operator overloading

	//Operator[] that takes an integer and works like the getLine function. 
	//It returns the program line as a string.
	const string CPUProgramDyn::operator [](const int number) const
	{
		if(number >= 0 && number < this->size())
		    return data[number];
		else
		{
		    cerr<<"[] operator range error.";
		    return "";
		}
	}
	const void CPUProgramDyn::setData(const string var) 
	{
		if( size() == getCapacity())
		{  
		    const int factor = 2; //factor of new capacity
		    string *temp = new string[ getCapacity()*factor ];
		    
		    for(int i = 0; i < size(); ++i )
		        temp[i] = data[i];
		    
		    delete [] data;
		    data = temp; //pointing new array 
		    capacity = getCapacity()*factor;
		}
		data[size()] = var;
		setSize(size()+1);
	}
	//deleting last data of string array
	const void CPUProgramDyn::delLastData() 
	{
		data[size()-1] = "\0";
		setSize(size()-1);
	}
	//comparison overloading functions,, compare the number of lines of the programs.
	const bool CPUProgramDyn::operator ==(const CPUProgramDyn &var) const
	{
		return (this->size() == var.size());
	}
	const bool CPUProgramDyn::operator > (const CPUProgramDyn &var) const 
	{
	   return (this->size() > var.size());
	}
	const bool CPUProgramDyn::operator < (const CPUProgramDyn &var) const
	{
		return (this->size() < var.size());
	}
	const bool CPUProgramDyn::operator <=(const CPUProgramDyn &var) const
	{
		return (this->size() <= var.size());
	}
	const bool CPUProgramDyn::operator >=(const CPUProgramDyn &var) const 
	{
		return (this->size() >= var.size());
	}
	const bool CPUProgramDyn::operator != (const CPUProgramDyn &var)const     
	{
		return (this->size() != var.size());
	}
	//that prints the program
	ostream& operator <<(ostream& outputStream, const CPUProgramDyn &var)
	{
		for(int i = 0; i < var.size(); ++i)
		{
		   if(i < var.size()-1)
		        outputStream << var.getData(i)<<endl;
		   else
		        outputStream << var.getData(i);
		}
		return outputStream;
	}
	//takes two integers and returns a new program that contains the instructions between the given integers.
	const CPUProgramDyn CPUProgramDyn::operator () (const int number1, const int number2) const
	{
		CPUProgramDyn newCPUProg;    
		if(number1 > number2 || number1<0 || number2<0 || number1>=size() || number2>=size()) //error check
		{
		    cerr << "() operator range error.";
		    return newCPUProg;
		}
				
		for(int i = number1; i <= number2; ++i)
		    newCPUProg.setData( getData( i ) );
		
		newCPUProg.setSize(number2 - number1 + 1);
		
		return newCPUProg;
	}
	const CPUProgramDyn CPUProgramDyn::operator -- (int) //postfix version, that delete the last line of the program.
	{
		CPUProgramDyn temp;
		for(int i=0; i<this->size(); ++i)
		{
		    temp.setData(this->getData(i));	
		}
		delLastData();

		return temp;
	}
	const void CPUProgramDyn::operator -- () //prefix version, that delete the last line of the program.
	{   
		delLastData();
	}
	//It returns a new CPUProgram that has the original CPUProgram with appended last line from the parameter string.
	const CPUProgramDyn CPUProgramDyn::operator +( const string newInstruction) const
	{
		CPUProgramDyn prog;
		if(newInstruction[0]=='\0') 
		{
		    cerr<<"You can not append empty string.";
		    return prog;
		}
		for(int i = 0; i < this->size(); ++i)
		    prog.setData( this->getData( i ) ) ;
		
		prog.setData( newInstruction ) ;  
		
		prog.setSize(this->size() + 1 );

		return prog;
	}
	//takes an instruction line as a string and appends the instruction to the end of the program.
	const void CPUProgramDyn::operator +=( const string newInstruction)
	{
		if(newInstruction[0]=='\0') 
		{
		    cerr<<"You can not append empty string."<<endl;
		}
		else
		    this->setData( newInstruction );    
	 
	}   
	//Operator+ that takes two programs and returns a new program that appends the second programs to the first one
	const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn &var1) const
	{ 
		CPUProgramDyn prog;
		for(int i = 0; i < size(); ++i)
		    prog.setData( this->getData( i ) ) ;
		
		for(int j = 0; j < var1.size(); ++j)
		    prog.setData( var1.getData( j ) ) ;
		
		prog.setSize(size() + var1.size() );
		
		return prog;
	}

	const void CPUProgramDyn::operator =(const CPUProgramDyn &var) 
	{
		fileName = var.fileName;
		fileIsOpen = var.fileIsOpen;
		option = var.option;
		capacity = var.capacity;
		totalSize = var.totalSize;
		
		for(int i=0; i<var.size(); ++i)
		{
			setData( getData(i) );
		}
		
	}
	//if any case lower case in file, convert to upper case
	const void CPUProgramDyn::uppercaseConverter(string &buffer) const
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
	const void CPUProgramDyn::ReadFile(const string FileName)
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
		        	setData(buffer);     
		    }
		    inp.close();
		}
	}
	
	
	//string simplification as per following conditions
	const string CPUProgramDyn::editSpacesAndTabs(string line) const
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
}
