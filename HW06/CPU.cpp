#include "CPU.h"
using namespace std;
//print errors or messages(such as print instructions command)
//if END true, error messages will print, else others
const void CPU::printErrorOrMessages () const
{
    if(!END)
    {
        for(int i = 0; i < messages.size(); ++i)
        {
            cout << messages[i] << endl;
        }
    }
    else
    {
        for(int i = 0; i < error.size(); ++i)
        {
            cout << error[i] << endl;
        }
    }
}
//control func. of negative assing to Memory element
const int CPU::logicErrorCase(const int &number) 
{
    if(number < 0)
    {
        cerr << "You can not assign negative number to Memory." << endl;
        END = true;
        exit(1);
    }
    else 
        return 0;
}
//execute function takes a string that contains an instruction line, executes it 
//and advances the PC accordingly
const void CPU::execute(const string &instLine, Memory &myMemory )
{	
   
    Instruction inst;
    string buffer, buffer2; //Manupulation strings
    int indicator; // cStrTok return value control variable

    buffer2 = instLine; // will executed string
    buffer2 = editSpacesAndTabs(buffer2); //string simplification
  
    indicator = cStrTok(buffer2, buffer, ' ');
    if(indicator != -1)
    {   
        instruction = buffer; //instruction will check in halted function in main

        if(buffer == "MOV") 
        {
            //check MOV instructure line syntax
            if(!movControl(buffer2, inst))
            { 
                if(inst.movProb1)
                {   
                    setRegister(inst.registerNumber2 - 1, getRegister(inst.registerNumber1 - 1));
                    setPC(getPC() + 1);
                }
                else if(inst.movProb2)
                {  
                    setRegister(inst.registerNumber1 - 1, inst.constant);
                    setPC(getPC() + 1);
                }
                else if(inst.movProb3 && !logicErrorCase(R[inst.registerNumber1-1]) )
                {  
                    myMemory.setMem(inst.adressNumber, getRegister(inst.registerNumber1 - 1));
                    setPC(getPC() + 1);
                }  
                else if(inst.movProb4)
                {   
                    setRegister(inst.registerNumber1-1, myMemory.getMem(inst.adressNumber));
                    setPC(getPC() + 1);
                }
                else if(inst.movProb5 && !logicErrorCase( inst.constant )) 
                {        
               
                    myMemory.setMem(inst.adressNumber, inst.constant);
                    setPC(getPC() + 1);
                }
            }
            else
            {
                string s1 = "Syntax Error! Check MOV instruction. ";
                error.push_back(s1);
                END = true;
            }
        }
        //check ADD instructure line syntax
        else if(buffer == "ADD") 
        {
            if(!addSubControl(buffer2, inst))
            {
                if(inst.addSubProb1)
                {   
                    setRegister( inst.registerNumber1 - 1, 
		            	getRegister(inst.registerNumber1 - 1) + 
		            	getRegister(inst.registerNumber2 - 1));
                    setPC(getPC()+1);
                }
                else if(inst.addSubProb2)
                {   
                    setRegister( inst.registerNumber1 - 1, 
		            	getRegister(inst.registerNumber1 - 1) + 
		            	inst.constant);
                    setPC(getPC()+1);
                }
                else if(inst.addSubProb3)
                { 
                    setRegister(inst.registerNumber1 - 1, 
                            getRegister(inst.registerNumber1 - 1) + 
                            myMemory.getMem(inst.adressNumber));
                    setPC(getPC()+1);
                }
            }
            else
            {
                string s1 = "Syntax Error! Check ADD instruction. ";
                error.push_back(s1);
                END = true;
            }
        }
        //check SUB instructure line syntax
        else if(buffer == "SUB") 
        {
            if(!addSubControl(buffer2, inst))
            {
                if(inst.addSubProb1)
                {   
                    setRegister( inst.registerNumber1 - 1, 
                            getRegister(inst.registerNumber1 - 1) - 
                            getRegister(inst.registerNumber2 - 1));
                    setPC(getPC()+1);
                }
                else if(inst.addSubProb2)
                {   
                    setRegister( inst.registerNumber1 - 1, 
                                getRegister(inst.registerNumber1 - 1) - 
                                inst.constant);
                    setPC(getPC()+1);
                }
                else if(inst.addSubProb3)
                {
                    setRegister(inst.registerNumber1 - 1, 
                            getRegister(inst.registerNumber1 - 1) - 
                            myMemory.getMem(inst.adressNumber));
                    setPC(getPC()+1);
                }
            }
            else
            {
                string s1 = "Syntax Error! Check SUB instruction. " ;
                error.push_back(s1);
                END = true;
            }
        }
        //check JMP instructure line syntax
        else if(buffer == "JMP")
        {
            if(!jmpControl(buffer2, inst))
            {    
                if(inst.jmpProb1)
                { 
                    if(R[inst.registerNumber1 - 1] == 0)
                    {
                        if(inst.lineAdress - 1 >= 0 && inst.lineAdress - 1 < 200)
                           setPC(inst.lineAdress - 1); 
                        else
                        {
                            string s1 = "JMP line adress should be between 1 and 200. ";
                            error.push_back(s1);
                            END = true;
                        }
                    }
                    else
                        setPC(getPC()+1);
                }
                else if(inst.jmpProb2)
                {
                    setPC(inst.lineAdress - 1);
                }
            }
            else
            {
                string s1 = "Syntax Error! Check JMP instruction. ";
                error.push_back(s1);
                END = true;
            }
        }
        //check PRN instructure line syntax
        else if(buffer == "PRN")
        {
            if(!prnControl(buffer2, inst))
            {   
                if(inst.prnProb1)
                {   
                    string s1 = intToString(inst.registerNumber1);
                    string s2 = intToString( getRegister(inst.registerNumber1 -1) );   
                    string s3 = "Value of R" + s1 + " is " + s2 + ".";
                    messages.push_back(s3);
                    setPC(getPC() + 1);
                }
                else if(inst.prnProb2)
                {
                    string s1 = intToString(inst.constant);
                    string s2 = "Constant value is " + s1 + "."  ;
                    messages.push_back(s2);
                    setPC(getPC() + 1);
                }
                else if(inst.prnProb3)
                {
                    string s1 = intToString(myMemory.getMem(inst.adressNumber));
                    string s2 = intToString(inst.adressNumber);
                    string s3 = "Value is " + s1 + " in adress of #" + s2 + ". " ;
                    messages.push_back(s3);
                    setPC(getPC() + 1);
                }
            }
            else 
            {
                string s1 = "Syntax Error! Check PRN instruction. ";
                error.push_back(s1);
                END = true;
            }
        }
        //check PRN instructure line syntax
        else if(buffer == "JPN")
          {
              if(!jpnControl(buffer2, inst))
              {
                  if(inst.jmpProb1)
                  {
                      if( R[inst.registerNumber1-1] <= 0)
                      {
                          if(inst.lineAdress - 1 >= 0 && inst.lineAdress - 1 < 200)
                              setPC(inst.lineAdress - 1);
                          else
                          {
                              string s1 = "JPN line adress should be between 0 and 199" ;
                              error.push_back(s1);
                              END = true;
                          }
                      }
                      else
                      {
                          setPC(getPC() + 1);
                      }
                  }
              }
          }
        //check HLT instructure line syntax
        else if(buffer == "HLT" )
        {
            if( buffer2.size() == 0)
                printErrorOrMessages ();
            else
            {
                string s1 = "Syntax Error! Check HLT instruction. ";
                error.push_back(s1);
                END = true;
            }
        }
        else
        {
            string s1 = "Instruction error! Missing or incorrect instruction.";
            error.push_back(s1);
            END = true;
        }

        if(getOption() == 1 || getOption() == 2)
        {
            string s1 =  instLine;
            s1 += "- R1=" + intToString( getRegister(0)) ; 
            s1 += ", R2=" + intToString( getRegister(1) ) ;
            s1 += ", R3=" + intToString( getRegister(2) ) ; 
            s1 += ", R4=" + intToString( getRegister(3) ) ; 
            s1 += ", R5=" + intToString( getRegister(4) ) ; 
            messages.push_back(s1);
        }
        if (getOption() == 2)
        { 
            string s1 = "Memory Values:" ;
            messages.push_back(s1);
            for(int i = 0; i < myMemory.getMemSize(); ++i)
            {
                s1 = "[" +  intToString(i) + "]" + " " +"->" + " "+ intToString(myMemory.getMem(i));
                messages.push_back(s1);
            }
        }
    }
    else
    {
        string s1 = "Instruction error! Missing or incorrect instruction.";
        error.push_back(s1);
        END = true;
    }
    if(END)
    {
        printErrorOrMessages ();
    }
}
//halted function returns true if the last instruction executed halted 
//the CPU or occured error.
const bool CPU::halted() const
{
    if(instruction == "HLT"  || END)
        return true;
    else
        return false;
}

//Take integer and convert to string and return that
const string CPU::intToString ( const int &num ) const
{
  ostringstream newString;
  
  newString << num;

  return newString.str();
}
/*
 * we have 2 probability for jmp instruction. This function check that probabilities
 * probability1 ; //if true mean that jmp reg,lineadres
 * probability2 ; //if true mean that jmp lineadress
 * 
 * @param1 string that except JMP characters
 * @param2 class of instructions
 */
const int CPU::jmpControl(string body, Instruction &inst) 
{
    string buffer, buffer2;  //manupulation strings
    int indicator;  
    int number=0;
    bool indicator2 = false;
    buffer2 = body;
    
    if(body.size() == 0)
        return -1;
    
    indicator = cStrTok(body, buffer, ',');
    
    if(indicator != -1 && buffer[0] == 'R' && buffer.size() == 2 )
    {
        indicator2 = stringConvToInt(buffer.substr(1),number);
        if( indicator2 && number >= 1 && number <= 5 )
        {
            inst.registerNumber1 = number;
            cStrTok(body, buffer2, ' ');
            indicator2 = stringConvToInt(buffer2, number);
            if(indicator2 )
            {
                inst.jmpProb1 = true;
                inst.lineAdress = number;
                return 0;
            }
        }
    }
    else 
    {
        cStrTok(buffer2, buffer, ' ');
        indicator2 = stringConvToInt(buffer, number);
        if(indicator2)
        {       
            inst.jmpProb2 = true;
            inst.lineAdress = number;
            return 0;
        }
        else
        {
            return -1; 
        }
        body = buffer2;
    }
    if(body.size() != 0)
        return -1;
    return -1;
}
/*
 * we have 3 probability for PRN instruction. This function check that probabilities
 * probability1 ; //if true mean that  PRN reg
 * probability2 ; //if true mean that PRN const
 * probability3 ; ////if true mean that PRN adress
 * @param1 string that except PRN characters
 * @param2 class of  instructions
 */
const int CPU::prnControl(string body, Instruction &inst) 
{
    string buffer, buffer2;  //manupulation strings
    int indicator;   
    int number=0;
    bool indicator2 = false;
    
    buffer2 = body; 
    
    if(body.size() == 0)
        return -1;
    indicator = cStrTok(body, buffer, ' ');
    
    indicator2 = stringConvToInt(buffer, number);
    
    if(buffer == "\0" || indicator == -1)
        return -1;

    if(buffer[0] == '#' && buffer.size() > 1)
    {
        indicator2 =  stringConvToInt(buffer.substr(1), number);
        if( indicator2)
        {
            inst.prnProb3 = true;
            inst.adressNumber = number;
            if(!body.size() ) return 0;
        }
    }
    else if(buffer[0] == 'R' && buffer.size() == 2)
    {
        indicator2 =  stringConvToInt(buffer.substr(1), number);
        if( indicator2 && number >= 1 && number <= 5 )
        {
            inst.prnProb1 = true;
            inst.registerNumber1 = number;
            if(!body.size() ) return 0;
        }        
    }
    else if(indicator2)
    {
        inst.prnProb2 = true;
        inst.constant = number;
        if(!body.size() ) return 0;
    }
    
    return -1;
}
/*
 * we have 5 probability for move instruction. This function check that probabilities
 *  probability1 ; //if true mean that MOV reg, reg
 *  probability2 ; //if true mean that MOV reg, constant
 *  probability3 ; //if true mean that MOV reg, adress
 *  probability4 ; //if true mean that MOV adress, reg
 *  probability5 ; //if true mean that MOV adress, constant
 * 
 * @param1 string that except MOV characters
 * @param2 struct of move instructions
 */
const int CPU::movControl(string body, Instruction &inst) 
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool indicator2 = false; 
    int number=0;
    
    if(body.size() == 0) return -1; //empty line control
    
    indicator = cStrTok(body, buffer, ',');
    if(indicator != -1)
    {
        if(buffer[0] == 'R' && buffer.size() == 2)
        {  
            indicator2 = stringConvToInt(buffer.substr(1), number);
            if( indicator2 && number >= 1 && number <= 5 )
            {
                inst.registerNumber1 = number; 
                cStrTok(body, buffer2, ' ');
                indicator2 = stringConvToInt(buffer2, number);
                if(buffer2[0] == 'R')
                {
                    if(buffer2.size() == 2 )
                    {   
                        indicator2 = stringConvToInt(buffer2.substr(1), number);
                        if( indicator2 && number >= 1 && number <= 5 )
                        { 
                            inst.registerNumber2 = number;
                            inst.movProb1 = true;
                            if(body[0] == '\0')  return 0; 
                        }
                    }
                }
                else if(buffer2[0] == '#')
                {   
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if(indicator2)
                    {
                        inst.adressNumber = number;
                        inst.movProb3 = true;
                        if(body[0] == '\0') return 0;
                    }
                }
                else if(indicator2)
                {  
                    inst.constant = number;
                    inst.movProb2 = true;
                    if(body[0] == '\0') return 0;
                }
            }
        }
        else if( buffer[0] == '#' && (buffer.size() == 2 || buffer.size() == 3) )
        {
            indicator2 = stringConvToInt(buffer.substr(1), number);     
            if(indicator2)
            {
                inst.adressNumber = number;    
                cStrTok(body, buffer2, ' ');
                indicator2 = stringConvToInt(buffer2, number);

                if(buffer2[0] == 'R' && buffer2.size() == 2)
                {
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if( indicator2 && number >= 1 && number <= 5 )
                    {
                        inst.registerNumber1 = number;
                        inst.movProb4 = true;
                        if(body[0] == '\0')  return 0;
                    }
                }
                else if(indicator2)
                {
                    inst.constant = number;
                    inst.movProb5 = true;
                    if(body[0] == '\0')  return 0;
                }          
            }
        }
    }
    return -1; // if func not return when come this command, error.
}
/*
 * we have 3 probability for add or sub instruction. This function check that probabilities
 * probability1 ; //if true mean that Add&Sub reg, reg
 * probability2 ; //if true mean that Add&Sub reg, constant
 * probability3 ; //if true mean that Add&Sub reg, adress
 * 
 * @param1 string that except ADD or SUB characters
 * @param2 class of instructions
 */
const int CPU::addSubControl(string body, Instruction &inst) 
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool indicator2 = false;
    int number;
    
    if(body.size() == 0) return -1;
    indicator = cStrTok(body, buffer, ',');
    
    if(indicator != -1)
    {
        if(buffer[0] == 'R' && buffer.size() == 2)
        {
            indicator2 = stringConvToInt(buffer.substr(1) , number);
            if( indicator2 && number >= 1 && number <= 5 )
            {
                inst.registerNumber1 = number;
                cStrTok(body, buffer2, ' ');
                indicator2 = stringConvToInt(buffer2, number);
                if(buffer2[0] == 'R' && buffer2.size() == 2)
                {
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if( indicator2 && number >= 1 && number <= 5 )
                    { 
                        inst.registerNumber2 = number;
                        inst.addSubProb1 = true;
                        if(body[0] == '\0') return 0; 
                    }    
                }
                else if(buffer2[0] == '#')
                {
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if( indicator2 )
                    {
                        inst.adressNumber = number;
                        inst.addSubProb3 = true;
                        if(body[0] == '\0') return 0;
                    }
                }
                else if( indicator2 )
                {   
                    inst.constant= number;
                    inst.addSubProb2= true;
                    if(body[0] == '\0') return 0;
                }
            }
        }
    } 
    return -1;
}
/*
 * we have 1 probability for jpn instruction. This function check that probability
 * probability1 ; //if true mean that JPN reg,lineadres * 
 * @param1 string that except JPN characters
 * @param2 struct of jpn instructions
 */
const int CPU::jpnControl(string body, Instruction &inst) 
{
    string buffer, buffer2;  //manupulation strings
    int indicator;  
    int number=0;
    bool indicator2 = false;
    buffer2 = body;
    
    if(body.size() == 0) return -1;
    indicator = cStrTok(body, buffer, ',');
    if(indicator !=-1 && buffer[0] == 'R' && buffer.size() == 2 )
    {
        indicator2 = stringConvToInt(buffer.substr(1), number);
        if( indicator2 && number >= 1 && number <= 5 )
        {
            inst.registerNumber1 = number;
            cStrTok(body, buffer2, ' ');
            indicator2 = stringConvToInt(buffer2, number);
            
            if(indicator2)
            {
                inst.jmpProb1 = true;
                inst.lineAdress = number;     
                return 0;
            }            
        }
    }
    if(body.size() != 0) return -1;
    return -1;
}
/*
 * It takes string and Number
 * if string contain only characters of numbers, convert to integer and
 * change @param2
 * 
 * if string contain except of char. of numbers, return false else return true
 */
const bool CPU::stringConvToInt(const string &myString, int &number)
{
    bool isNegative = false;
    int j = 0;
    number = 0;
    if( myString.size() > 1 && myString[0] == '-')
    {
        isNegative = true;
        j = 1;
    }
    for(int i = j; i < myString.size(); ++i)
    {
        if( myString[i] >= 48 && myString[i] <= 57 )
        {
            number *= 10;
            number += myString[i] - '0';
        }
        else
        {
            return false;
        }
    }
    if(isNegative) number *= -1;
    if(myString.size() == 0) 
        return false;
    else
        return true;
}
/* if return -1, not match.
 * @param1 string, output parameter. new string after parsing
 * @param2 buffer, output parameter. parsed parameter
 * @param3 delim, delimeters.
 */
const int CPU::cStrTok(string &strng, string &buffer, const char &delim) const
{
    int index = strng.find_first_of(delim);
    if(index != -1)
    {
        string s1 = strng.substr(0, index);
        buffer = s1;
        string s2 = strng.substr(index+1);
        strng = s2;
    }
    else
        return -1;
   
    return 0; 
}
//convert string to integer. arg must be 1 or 0, else return -1 (error)
const int CPU::stringToInteger(const string &arg) 
{
    int number;
    if(arg.size() != 1)
        return -1;
    number = arg[0] - '0';
    if(number == 0 || number == 1 || number == 2)
        return number;
    else return -1;
}
//Constructure of CPU class
CPU::CPU()
{
    for(int i = 0; i < 5; i++)
        R[i]  = 0;
    PC = 0;
}

//Constructure of CPU class
CPU::CPU(const int number)
{
    for(int i = 0; i < 5; i++)
        R[i]  = 0;
    PC = 0;
    setOption(number);
}
//print registers
const void CPU::print() const
{
    cout << "Program Counter: " << getPC() << endl;
    cout << "CPU Register Values: " << endl;
    for(int i = 0; i < 5; ++i)
    {
        cout << "[" <<  i << "]" << "->" << getRegister(i) << endl; 
    }
}


//string simplification as per following conditions
const string CPU::editSpacesAndTabs(string line) const
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