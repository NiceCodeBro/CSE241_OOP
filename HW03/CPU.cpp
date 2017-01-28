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
//execute function takes a string that contains an instruction line, executes it 
//and advances the PC accordingly
const void CPU::execute(const string &instLine )
{	
    Instruction inst;
    string buffer, buffer2; //Manupulation strings
    int indicator; // cStrTok return value control variable

    buffer2 = instLine; // will executed string
    indicator = cStrTok(buffer2, buffer, ' ');
    if(indicator != -1)
    {
        instruction = buffer; //instruction will check in halted function in main
        if(buffer == "MOV") 
        {
            //check MOV instructure line syntax
            if(!addMovSubControl(buffer2, inst))
            { 
                if(inst.MovAddSubProb1)
                {   
                	setRegister(inst.MovAddSubRegNum2 - 1, getRegister(inst.MovAddSubRegNum1 - 1));
                    setPC(getPC() + 1);
                }
                else if(inst.MovAddSubProb2)
                {  
                	setRegister(inst.MovAddSubRegNum1 - 1, inst.MovAddSubConst);
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
            if(!addMovSubControl(buffer2, inst))
            {
                if(inst.MovAddSubProb1)
                {   
                	setRegister( inst.MovAddSubRegNum1 - 1, 
		            	getRegister(inst.MovAddSubRegNum1 - 1) + 
		            	getRegister(inst.MovAddSubRegNum2 - 1));
                    setPC(getPC()+1);
                }
                else if(inst.MovAddSubProb2)
                {   
               		setRegister( inst.MovAddSubRegNum1 - 1, 
		            	getRegister(inst.MovAddSubRegNum1 - 1) + 
		            	inst.MovAddSubConst);
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
            if(!addMovSubControl(buffer2, inst))
            {
                if(inst.MovAddSubProb1)
                {   
                	setRegister( inst.MovAddSubRegNum1 - 1, 
		            	getRegister(inst.MovAddSubRegNum1 - 1) - 
		            	getRegister(inst.MovAddSubRegNum2 - 1));
                    setPC(getPC()+1);
                }
                else if(inst.MovAddSubProb2)
                {   
		            setRegister( inst.MovAddSubRegNum1 - 1, 
				        	getRegister(inst.MovAddSubRegNum1 - 1) - 
				        	inst.MovAddSubConst);
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
                    if(R[inst.jmpRegNum1 - 1] == 0)
                    {
                        if(inst.jmpLineAdress - 1 >= 0 && inst.jmpLineAdress - 1 < 200)
                           setPC(inst.jmpLineAdress - 1); 
                        else
                        {
                            string s1 = "JMP line adress should be between 1 and 200";
                            error.push_back(s1);
                            END = true;
                        }
                    }
                    else
                        setPC(getPC()+1);
                }
                else if(inst.jmpProb2)
                {
                    setPC(inst.jmpLineAdress - 1);
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
                    string s1 = intToString(inst.prnRegNum1);
                    string s2 = intToString( getRegister(inst.prnRegNum1 -1) );   
                    string s3 = "Value of R" + s1 + " is " + s2 + ".";
                    messages.push_back(s3);
                    setPC(getPC() + 1);
                }
                else if(inst.prnProb2)
                {
                    string s1 = intToString(inst.prnConst);
                    string s2 = "Constant value is " + s1 + "."  ;
                    messages.push_back(s2);
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
        //check MOV instructure line syntax
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
        
        if(option)
        {
            string s1 =  instLine;
            s1 += "- R1=" + intToString( getRegister(0)) ; 
            s1 += ", R2=" + intToString( getRegister(1) ) ;
            s1 += ", R3=" + intToString( getRegister(2) ) ; 
            s1 += ", R4=" + intToString( getRegister(3) ) ; 
            s1 += ", R5=" + intToString( getRegister(4) ) ; 
            messages.push_back(s1);
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
            inst.jmpRegNum1 = number;
            cStrTok(body, buffer2, ' ');
            indicator2 = stringConvToInt(buffer2, number);
            if(indicator2 )
            {
                inst.jmpProb1 = true;
                inst.jmpLineAdress = number;
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
            inst.jmpLineAdress = number;
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
 * probability1 ; //if true mean that  PRN adress
 * probability2 ; //if true mean that PRN reg
 * 
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

    if(buffer[0] == 'R' && buffer.size() == 2)
    {
        indicator2 =  stringConvToInt(buffer.substr(1), number);
        if( indicator2 && number >= 1 && number <= 5 )
        {
            inst.prnProb1 = true;
            inst.prnRegNum1 = number;
            return 0;
        }        
    }
    else if(indicator2)
    {
        inst.prnProb2 = true;
        inst.prnConst = number;
        return 0;
    }
    if(body.size() != 0)
        return -1;
    
    return -1;
}

/*
 * we have 3 probability for add or sub instruction. This function check that probabilities
 * probability1 ; //if true mean that addSubMov reg, reg
 * probability2 ; //if true mean that addSubMov reg, constant
 * 
 * @param1 string that except MOV, ADD or SUB characters
 * @param2 class of instructions
 */
const int CPU::addMovSubControl(string body, Instruction &inst)
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool indicator2 = false;
    int number;
    
    if(body.size() == 0)
        return -1;
    indicator = cStrTok(body, buffer, ',');
    
    if(indicator != -1)
    {
        if(buffer[0] == 'R' && buffer.size() == 2)
        {
            indicator2 = stringConvToInt(buffer.substr(1) , number);
            if( indicator2 && number >= 1 && number <= 5 )
            {
                inst.MovAddSubRegNum1 = number;
                cStrTok(body, buffer2, ' ');
                indicator2 = stringConvToInt(buffer2, number);
                if(buffer2[0] == 'R')
                {
                    if(buffer2.size() == 2 )
                    {
                        indicator2 = stringConvToInt(buffer2.substr(1), number);
                        if( indicator2 && number >= 1 && number <= 5 )
                        { 
                            inst.MovAddSubRegNum2 = number;
                            inst.MovAddSubProb1 = true;
                            if(body[0] == '\0')
                                return 0; 
                        }   
                    }  
                }
                else if( indicator2 )
                {   
                    inst.MovAddSubConst = number;
                    inst.MovAddSubProb2 = true;
                    if(body[0] == '\0')
                        return 0;
                }
            }
        }
    } 
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

//print registers
const void CPU::print() const
{
    cout << "Program Counter = " << PC << " R1 = " << getRegister(0) << " R2 = " << getRegister(1)
         << " R3 = " << getRegister(2) << " R4 = " << getRegister(3) << " R5 = " << getRegister(4) << endl ;
}
