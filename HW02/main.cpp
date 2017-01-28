/*
    GEBZE TECHNICAL UNIVERSITY
    CSE241 HW#2
    MUHAMMED SELIM DURSUN
    1301044023 
 
    Program that will simulate a very simple CPU. CPU has only 5 registers
    (R1, R2, R3, R4, R5) and no other memory. 
    This homework is continue of hw1. 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct MoveInstructions
{
    bool probability1 ; //if true mean that MOV reg, reg
    bool probability2 ; //if true mean that MOV reg, constant
    bool probability3 ; //if true mean that MOV reg, adress
    bool probability4 ; //if true mean that MOV adress, reg
    bool probability5 ; //if true mean that MOV adress, constant
    int registerNumber1, registerNumber2 ; // if need, registerNumber2 using 
    int adressNumber ;
    int constant ;

};
struct addSubInstructions
{
    bool probability1 ; //if true mean that Add&Sub reg, reg
    bool probability2 ; //if true mean that Add&Sub reg, constant
    bool probability3 ; //if true mean that Add&Sub reg, adress
    int registerNumber1, registerNumber2 ; // if need, registerNumber2 using 
    int adressNumber ;
    int constant ;

};

struct prnInstructions
{
    bool probability1 ; //if true mean that PRN reg
    bool probability2 ; //if true mean that PRN constant 
    bool probability3 ; //if true mean that PRN adress
    int registerNumber;
    int adressNumber ;
    int constant;
};

struct jmpInstructions
{
    bool probability1 ; //if true mean that JMP reg, lineadress
    bool probability2 ; //if true mean that JMP lineadress 
    int registerNumber;
    int lineadress;
};

struct jpnInstructions
{
    bool probability1 ; //if true mean that JPN reg, lineadress
    int registerNumber;
    int lineadress;
};

//init jmpInstructions struct
void initJmp(jmpInstructions &jmp);
//init jpnInstructions struct
void initJpn(jpnInstructions &jpn);
//init prnInstructions struct
void initPrn(prnInstructions &prn);
//init addSubInstructions struct
void initAddSubInstructions(addSubInstructions &addSub);
//init MoveInstructions struct
void initMoveInstructions(MoveInstructions &mov);
//init registers to 0
void initRegisters(int R[], int size);
void initMemory(unsigned int memory[], int maxMemoryNum);
//if there any lower case char, converting to uppercase
void uppercaseConverter(string &buffer);

/*
 * Read file, changing string. if any chars lower case, convert to upper case
 * Update number of the filled line of string array
 */
void readFileAndFillDataArray(fstream *inp, string *data, int *num );

/*
 * Read instructions and call related function, and moves to next line
 * @param1 *data >> string array, max line numbers 200
 * @param2 R >> symbolize registers that R1,R2,R3,R4,R5
 * @param3 maxData >> size of string array
 * @param4 MemoryNum >> memory size
 * @param5 *Memory >> unsigned int memory array
 * @param6 option >> work kind of debugger, if option 1, print all operations
 */
void mainProcess(string *data, int R[], int maxData, const int MemoryNum, 
        unsigned int memory[],int &option );

//string simplification as per following conditions
string editSpacesAndTabs(string line);

//convert string to integer. arg must be 1 or 0, else return -1 (error)
int stringToInteger(string arg);

/* if return -1, not match.
 * @param1 string, output parameter. new string after parsing
 * @param2 buffer, output parameter. parsed parameter
 * @param3 delim, delimeters.
 */
int cStrTok(string &strng, string &buffer, char delim);

/*
 * It takes string and Number
 * if string contain only characters of numbers, convert to integer and
 * change @param2
 * 
 * if string contain except of char. of numbers, return false else return true
 */
bool stringConvToInt(string myString,  int &number);

//Take integer and convert to string and return that
string intToString ( int num );

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
int movControl(string body, MoveInstructions &mov);

/*
 * we have 3 probability for add or sub instruction. This function check that probabilities
 * probability1 ; //if true mean that Add&Sub reg, reg
 * probability2 ; //if true mean that Add&Sub reg, constant
 * probability3 ; //if true mean that Add&Sub reg, adress
 * 
 * @param1 string that except ADD or SUB characters
 * @param2 struct of addSub instructions
 */
int addSubControl(string body, addSubInstructions &addSub);

/*
 * we have 3 probability for PRN instruction. This function check that probabilities
 * probability1 ; //if true mean that  PRN adress
 * probability2 ; //if true mean that PRN reg
 * probability3 ; //if true mean that PRN const
 * 
 * @param1 string that except PRN characters
 * @param2 struct of prn instructions
 */
int prnControl(string body, prnInstructions &prn);

/*
 * we have 2 probability for jmp instruction. This function check that probabilities
 * probability1 ; //if true mean that jmp reg,lineadres
 * probability2 ; //if true mean that jmp lineadress
 * 
 * @param1 string that except JMP characters
 * @param2 struct of jmp instructions
 */
int jmpControl(string body, jmpInstructions &jmp);

/*
 * we have 1 probability for jpn instruction. This function check that probability
 * probability1 ; //if true mean that JPN reg,lineadres * 
 * @param1 string that except JPN characters
 * @param2 struct of jpn instructions
 */
int jpnControl(string body, jpnInstructions &jpn);

//checks the limits of same variables of structure
void errorStatus(jmpInstructions jmp, MoveInstructions mov, jpnInstructions jpn, 
        addSubInstructions addSub, prnInstructions prn, bool &END );

//check that if @param1 small from zero. If ok print error message and return -1
//else return 0
int logicErrorCase(int number);

int main(int argc, char** argv) {
    const int registerNums = 5; //number of register
    const int maxDataNum = 200; //number of line(data) of file 
    const int maxMemoryNum = 50; //number of memory 
    bool indicator = false; 
    int option; //option of terminal entry
    int number;
    string data[maxDataNum];
    fstream inp; //file stream
    // represent registers, R[0]=R1, R[1]=R2, R[2]=R3, R[3]=R4, R[4]=R5
    int R[registerNums]; 
    unsigned int memory[maxMemoryNum];
    initRegisters(R, registerNums); 
    initMemory(memory, maxMemoryNum);
    
 
    if(argc != 3)
    {
    	cout << "missing or too argument" << endl;
    	return -1;
    }
    option = stringToInteger(argv[2]);
    if(option == -1 )
    {
        cout << "Invalid option !" << endl;
        return -1;
    }
    inp.open(argv[1]);
    
    if (!inp.is_open()){
        cout << "can't open the file" << endl;
        return -1;
    }
    readFileAndFillDataArray(&inp, data, &number); 
    mainProcess(data, R, maxDataNum, maxMemoryNum,memory, option);
    return 0;
}

//initializing to memory element to zero
void initMemory(unsigned int memory[], int maxMemoryNum)
{
    for(int i = 0; i < maxMemoryNum; ++i)
    {
        memory[i] = 0;
    }
}


/*
 * Read instructions and call related function, and moves to next line
 * @param1 *data >> string array, max line numbers 200
 * @param2 R >> symbolize registers that R1,R2,R3,R4,R5
 * @param3 maxData >> size of string array
 * @param4 MemoryNum >> memory size
 * @param5 *Memory >> unsigned int memory array
 * @param6 option >> work kind of debugger, if option 1, print all operations
 */
void mainProcess(string *data, int R[], int maxData, const int MemoryNum, 
        unsigned int memory[],int &option )
{
    MoveInstructions mov;
    addSubInstructions addSub;
    prnInstructions prn;
    jmpInstructions jmp;
    jpnInstructions jpn;
    
    const int maxMessageNumbers = 1000;
    int line = 0;
    int pLine; //line's non enhanced version
    int messagesIndex = 0;
    
    //if there is not error, messages string content will print
    string messages[maxMessageNumbers];
    //manupulation strings
    string buffer; 
    string buffer2;
    
    bool END = false; //loop control var.
    bool ERROR = false;
    bool HLT = false;
    int indicator;
    int returnValue;
    
    
    initMoveInstructions(mov);
    initAddSubInstructions(addSub);
    initPrn(prn);
    initJmp(jmp);
    initJpn(jpn);
    
    maxData = 0;
    
    while(!END)
    {
        pLine = line;
        buffer2 = data[line];
        indicator = cStrTok(buffer2, buffer, ' '); //parsing

        if(indicator != -1)
        {
            if(buffer == "MOV")
            {
                returnValue = movControl(buffer2, mov);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {
                    if(mov.probability1)
                    {   
                        R[mov.registerNumber1 - 1] = R[mov.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(mov.probability2)
                    {   
                        R[mov.registerNumber1 - 1] = mov.constant;
                        line += 1;
                    }
                    else if(mov.probability3 )
                    {   
                        if(!logicErrorCase(R[mov.registerNumber1-1]))
                        {
                            memory[mov.adressNumber] = R[mov.registerNumber1-1];
                            line += 1;
                        }
                        else
                        {
                            END = true;
                            ERROR = true;
                        }
                    }  
                    else if(mov.probability4)
                    {   
                        R[mov.registerNumber1-1] = memory[mov.adressNumber];
                        line += 1;
                    }
                    else if(mov.probability5) 
                    {  
                        if(!logicErrorCase( mov.constant ))
                        {
                            memory[mov.adressNumber] = mov.constant;
                            line += 1;
                        }
                        else
                        {
                            END = true;
                            ERROR = true;
                        }
                    }

                    initMoveInstructions(mov);
                }
                else
                {
                    ERROR = true;
                    END = true;
                }
            }

            else if(buffer == "ADD")
            {   
                returnValue = addSubControl(buffer2, addSub);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {
                    if(addSub.probability1)
                    {
                        R[addSub.registerNumber1 - 1] += R[addSub.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(addSub.probability2)
                    {
                        R[addSub.registerNumber1 - 1] += addSub.constant;
                        line += 1;
                    }
                    else if(addSub.probability3)
                    {
                        R[addSub.registerNumber1 - 1] += memory[addSub.adressNumber ];
                        line += 1;
                    }
                    initAddSubInstructions(addSub);
                }
                else
                {
                    ERROR = true;
                    END = true;
                }   
            }
            else if(buffer == "SUB")
            {   
                returnValue = addSubControl(buffer2, addSub);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {  
                    if(addSub.probability1)
                    {
                        R[addSub.registerNumber1 - 1] -= R[addSub.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(addSub.probability2)
                    {
                        R[addSub.registerNumber1 - 1] -= addSub.constant;
                        line += 1;
                    }
                    else if(addSub.probability3)
                    {
                        R[addSub.registerNumber1 - 1] -= memory[addSub.adressNumber];
                        line += 1;
                    }
                    initAddSubInstructions(addSub);
                }
                else
                {
                    ERROR = true;
                    END = true;
                }
            }

            else if(buffer == "PRN")
            {
                returnValue = prnControl(buffer2, prn);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {   
                    if(prn.probability1)
                    {   
                        string s1 = intToString(prn.registerNumber);
                        string s2 = intToString(R[prn.registerNumber-1]);
                        messages[messagesIndex] = "Value of R" + s1 + " is " + s2;
                        line += 1;
                        messagesIndex += 1;
                    }
                    else if(prn.probability2)
                    {
                        string s1 = intToString(prn.constant);
                        messages[messagesIndex] = "Constan value is " + s1;
                        line += 1;
                        messagesIndex += 1;
                    }
                    else if(prn.probability3)
                    {
                        string s1 = intToString(memory[prn.adressNumber]);
                        string s2 = intToString(prn.adressNumber);
                        messages[messagesIndex] = "Value is " + s1 + " in adress of #" + s2 ;
                        line += 1;
                        messagesIndex += 1;
                    }
                    initPrn(prn);
                }
                else
                {
                    ERROR = true;
                    END = true;
                }
            }
            else if(buffer == "JMP")
            {
                returnValue = jmpControl(buffer2, jmp);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {   
                    if(jmp.probability1)
                    { 
                        if(R[jmp.registerNumber-1] == 0)
                        {
                            if(jmp.lineadress - 1 >= 0 && jmp.lineadress - 1 < 200)
                                line = jmp.lineadress - 1;
                            else
                            {
                                cout << "JMP line adress should be between 0 and 199" << endl;
                                END = true;
                                ERROR = true;
                            }
                        }
                        else
                            line +=1;
                    }
                    else if(jmp.probability2)
                    {
                        line = jmp.lineadress - 1;
                    }
                    initJmp(jmp);
                }
                else
                {
                    ERROR = true;
                    END = true;
                }
            }
            else if(buffer == "JPN")
            {
                returnValue = jpnControl(buffer2, jpn);
                errorStatus(jmp, mov, jpn, addSub, prn, END );
                if(!returnValue && !END)
                {
                    if(jpn.probability1)
                    {
                        if( R[jpn.registerNumber-1] <= 0)
                        {
                            if(jpn.lineadress - 1 >= 0 && jpn.lineadress - 1 < 200)
                                line = jpn.lineadress - 1;
                            else
                            {
                                cout << "JPN line adress should be between 0 and 199" << endl;
                                END = true;
                                ERROR = true;
                            }
                        }
                        else
                        {
                            line += 1;
                        }
                    }
                }
            }
            else if(buffer == "HLT")
            {
                option = 2;
                HLT = true; 
                END = true;
            }
            else
            {
                ERROR = true;
                END = true;
            }
        }
        else
        {
            ERROR = true;
            END = true;
        }
        if((option == 1 || option == 2) && (!END || HLT))
        {
            string s1 = intToString(R[0]);
            string s2 = intToString(R[1]);
            string s3 = intToString(R[2]);
            string s4 = intToString(R[3]);
            string s5 = intToString(R[4]);
            messages[messagesIndex] = data[pLine] + "- R1 = " + s1 + 
                                      ", R2 = " + s2 + ", R3 = " + s3 + 
                                      ", R4 = " + s4 + ", R5 = " + s5;
            ++messagesIndex;
        }
        if(option == 2 && (!END || HLT))
        {
            messages[messagesIndex] = data[pLine];
            
            for(int i=0; i < MemoryNum; ++i)
            {
                string s1 = intToString(i);
                string s2 = intToString(memory[i]);
                string s3 = "- #" + s1 + " = " + s2 + " ";
                messages[messagesIndex] += s3;
            }
            
            ++messagesIndex;
        }
                                     
    }
   
    
    if(END && ERROR)
    {
        cout << "Syntax or Logical Error !" << endl;
    }
    else if(END && !ERROR)
    {
        for(int i = 0; i < messagesIndex; ++i )
        {
            cout << messages[i] << endl;
        }
    }
}
//check that if @param1 small from zero. If ok print error message and return -1
//else return 0
int logicErrorCase(int number)
{
    if(number < 0)
    {
        cout << "You can not assign negative number to adress." << endl;
        return -1;
    }
    else 
        return 0;
}
/*
 * we have 1 probability for jpn instruction. This function check that probability
 * probability1 ; //if true mean that JPN reg,lineadres * 
 * @param1 string that except JPN characters
 * @param2 struct of jpn instructions
 */
int jpnControl(string body, jpnInstructions &jpn)
{
    string buffer, buffer2;  //manupulation strings
    int indicator;  
    int number=0;
    bool indicator2 = false;
    buffer2 = body;
    
    if(body.size() == 0)
        return -1;
    indicator = cStrTok(body, buffer, ',');
    if(indicator !=-1 && buffer[0] == 'R' && buffer.size() == 2 )
    {
        indicator2 = stringConvToInt(buffer.substr(1), number);
        
        if( indicator2 && number >= 1 && number <= 5 )
        {
            
            jpn.registerNumber = number;
            cStrTok(body, buffer2, ' ');
            indicator2 = stringConvToInt(buffer2, number);
            
            if(indicator2)
            {
                jpn.probability1 = true;
                jpn.lineadress = number;
                
            }
            else
            {
                return -1;
            }
            
        }
        else
        { 
            return -1;
        }
    }
    

    if(body.size() != 0)
        return -1;
    
    return 0;
}
/*
 * we have 2 probability for jmp instruction. This function check that probabilities
 * probability1 ; //if true mean that jmp reg,lineadres
 * probability2 ; //if true mean that jmp lineadress
 * 
 * @param1 string that except JMP characters
 * @param2 struct of jmp instructions
 */
int jmpControl(string body, jmpInstructions &jmp)
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
            
            jmp.registerNumber = number;
            cStrTok(body, buffer2, ' ');
            indicator2 = stringConvToInt(buffer2, number);
            if(indicator2 )
            {
                jmp.probability1 = true;
                jmp.lineadress = number;
            }
            else
            {
                return -1;
            }
            
        }
        else
        {
            return -1;
        }
    }
    else 
    {
        cStrTok(buffer2, buffer, ' ');
        indicator2 = stringConvToInt(buffer, number);
        if(indicator2)
        {       

            jmp.probability2 = true;
            jmp.lineadress = number;
        }
        else
        {
            return -1;
        }
        body = buffer2;
    }

    if(body.size() != 0)
        return -1;
    return 0;
}
/*
 * we have 3 probability for PRN instruction. This function check that probabilities
 * probability1 ; //if true mean that  PRN adress
 * probability2 ; //if true mean that PRN reg
 * probability3 ; //if true mean that PRN const
 * 
 * @param1 string that except PRN characters
 * @param2 struct of prn instructions
 */
int prnControl(string body, prnInstructions &prn)
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
            prn.probability3  = true;
            prn.adressNumber = number;
        }
        else
        {
            return -1;
        }
    }
    else if(buffer[0] == 'R' && buffer.size() == 2)
    {
        indicator2 =  stringConvToInt(buffer.substr(1), number);
        if( indicator2 && number >= 1 && number <= 5 )
        {
            prn.probability1 = true;
            prn.registerNumber = number;
        }
        else
        {
            return -1;
        }
        
    }
    else if(indicator2)
    {
        prn.probability2 = true;
        prn.constant = number;
    }
    else
    {
        return -1;
    }
    
    if(body.size() != 0)
        return -1;
    
    return 0;
}

/*
 * we have 3 probability for add or sub instruction. This function check that probabilities
 * probability1 ; //if true mean that Add&Sub reg, reg
 * probability2 ; //if true mean that Add&Sub reg, constant
 * probability3 ; //if true mean that Add&Sub reg, adress
 * 
 * @param1 string that except ADD or SUB characters
 * @param2 struct of addSub instructions
 */
int addSubControl(string body, addSubInstructions &addSub)
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool isConstantPositive = true;
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
                addSub.registerNumber1 = number;
                cStrTok(body, buffer2, ' ');
               
                indicator2 = stringConvToInt(buffer2, number);
                if(buffer2[0] == 'R')
                {
                    if(buffer2.size() == 2 )
                    {
                        indicator2 = stringConvToInt(buffer2.substr(1), number);
                        if( indicator2 && number >= 1 && number <= 5 )
                        { 
                            addSub.registerNumber2 = number;
                            addSub.probability1 = true;
                             if(body[0] == '\0')
                                return 0;
                            else
                                return -1;
                        }
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if(buffer2[0] == '#')
                {
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if( indicator2 )
                    {
                        addSub.adressNumber = number;
                        addSub.probability3 = true;
                        if(body[0] == '\0')
                            return 0;
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if( indicator2 )
                {   
                    addSub.constant = number;
                    addSub.probability2 = true;
                    if(body[0] == '\0')
                        return 0;
                    else
                        return -1;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        return -1;
    }
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
int movControl(string body, MoveInstructions &mov)
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool indicator2 = false; 
    int number=0;
    
    if(body.size() == 0)
        return -1;
    indicator = cStrTok(body, buffer, ',');
    
    if(indicator != -1)
    {
        if(buffer[0] == 'R' && buffer.size() == 2)
        {  
            indicator2 = stringConvToInt(buffer.substr(1), number);
            if( indicator2 && number >= 1 && number <= 5 )
            {
                mov.registerNumber1 = number; 
                cStrTok(body, buffer2, ' ');
                indicator2 = stringConvToInt(buffer2, number);
                if(buffer2[0] == 'R')
                {
                    if(buffer2.size() == 2 )
                    {   
                        indicator2 = stringConvToInt(buffer2.substr(1), number);
                        if( indicator2 && number >= 1 && number <= 5 )
                        { 
                            mov.registerNumber2 = number;
                            mov.probability1 = true;
                             if(body[0] == '\0')
                                return 0;
                            else
                                return -1;
                        }
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if(buffer2[0] == '#')
                {   
                    indicator2 = stringConvToInt(buffer2.substr(1), number);
                    if(indicator2)
                    {
                        mov.adressNumber = number;
                        mov.probability3 = true;
                        if(body[0] == '\0')
                            return 0;
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if(indicator2)
                {  
                    mov.constant = number;
                    mov.probability2 = true;
                    if(body[0] == '\0')
                        return 0;
                    else
                        return -1;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
        else if( buffer[0] == '#' && (buffer.size() == 2 || buffer.size() == 3) )
        {

            indicator2 = stringConvToInt(buffer.substr(1), number);
            
            if(indicator2)
            {
                mov.adressNumber = number;
                
                cStrTok(body, buffer2, ' ');
          
                indicator2 = stringConvToInt(buffer2, number);

                if(buffer2[0] == 'R')
                {
                    if(buffer2.size() == 2 )
                    {

                        indicator2 = stringConvToInt(buffer2.substr(1), number);
                        if( indicator2 && number >= 1 && number <= 5 )
                        {
                            mov.registerNumber1 = number;
                            mov.probability4 = true;
                             if(body[0] == '\0')
                                return 0;
                            else
                                return -1;
                        }
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else if(indicator2)
                {
                    mov.constant = number;
                    mov.probability5 = true;
                    if(body[0] == '\0')
                        return 0;
                    else
                        return -1;
                }
                else
                {
                    return -1;
                }
                
            }
            else
                return -1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
/*
 * It takes string and Number
 * if string contain only characters of numbers, convert to integer and
 * change @param2
 * 
 * if string contain except of char. of numbers, return false else return true
 */
bool stringConvToInt(string myString, int &number)
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

//checks the limits of same variables of structure
void errorStatus(jmpInstructions jmp, MoveInstructions mov, jpnInstructions jpn, 
        addSubInstructions addSub, prnInstructions prn, bool &END )
{
    if(jmp.lineadress<0 || jmp.lineadress>199)
    {
        END = true;
        cout << "Line adress can not be negative or bigger than 200." << endl;

    }
    if(mov.adressNumber < 0 || mov.adressNumber>49)
    {
        END = true;
        cout << "Adress number can not be negative or bigger than 200." << endl;
    }
    if(jpn.lineadress < 0 || jpn.lineadress > 199)
    {
        END = true;
        cout << "Line adress can not be negative or bigger than 200." << endl;
    
    }
    if(addSub.adressNumber  < 0 || addSub.adressNumber > 49)
    {
        END = true;
        cout << "Adress number can not be negative or bigger than 200." << endl;
    }
    if(prn.adressNumber < 0 || prn.adressNumber > 49)
    {
        END = true;
        cout << "Adress number can not be negative or bigger than 200." << endl;
    }
}
//init jmpInstructions struct
void initJmp(jmpInstructions &jmp)
{
    jmp.probability1 = false;
    jmp.probability2 = false;
    jmp.lineadress = 0;
    jmp.registerNumber = 0;
}
//init MoveInstructions struct
void initMoveInstructions(MoveInstructions &mov)
{
    mov.probability1 = false;
    mov.probability2 = false;
    mov.probability3 = false;
    mov.probability4 = false;
    mov.probability5 = false;
    mov.adressNumber = 0;
    mov.constant = 0;
    mov.registerNumber1 = 0;
    mov.registerNumber2 = 0;
}
//init jpnInstructions struct
void initJpn(jpnInstructions &jpn)
{
    jpn.probability1 = false;
    jpn.lineadress = 0;
    jpn.registerNumber = 0;
}
//init addSubInstructions struct
void initAddSubInstructions(addSubInstructions &addSub)
{
    addSub.probability1 = false;
    addSub.probability2 = false;
    addSub.probability3 = false;
    addSub.adressNumber = 0;
    addSub.constant = 0;
    addSub.registerNumber1 = 0;
    addSub.registerNumber2 = 0;
}
//init prnInstructions struct
void initPrn(prnInstructions &prn)
{
    prn.probability1 = false;
    prn.probability2 = false;
    prn.probability3 = false;
    prn.adressNumber = 0;
    prn.constant = 0;
    prn.registerNumber = 0;
}

//init registers to 0
void initRegisters(int R[], int size)
{
    for(int i = 0; i < size; ++i)
        R[i] = 0;
}


//if there any lower case char, converting to uppercase
void uppercaseConverter(string &buffer)
{
    for(int i=0; i<(buffer).size();++i)
    {
        if(buffer[i] >= 'a' && buffer[i] <= 'z')
            buffer[i] -= 'a' - 'A';
    }
}

/*
 * Read file, changing string. if any chars lower case, convert to upper case
 * Update number of the filled line of string array
 */
void readFileAndFillDataArray(fstream *inp, string *data, int *num )
{
    string buffer;
    string x;
    while(!(*inp).eof()){
        getline((*inp), buffer);
        buffer = editSpacesAndTabs(buffer); //string simplification
        uppercaseConverter(buffer);
        data[*num] = buffer;
        if(!(*inp).eof()) (*num)++;
    }
}

//string simplification as per following conditions
string editSpacesAndTabs(string line)
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
/* if return -1, not match.
 * @param1 string, output parameter. new string after parsing
 * @param2 buffer, output parameter. parsed parameter
 * @param3 delim, delimeters.
 */
int cStrTok(string &strng, string &buffer, char delim)
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
//Take integer and convert to string and return that
string intToString ( int num )
{
  ostringstream newString;
  
  newString << num;

  return newString.str();
}
//convert string to integer. arg must be 1 or 0, else return -1 (error)
int stringToInteger(string arg)
{
    int number;
    if(arg.size() != 1)
        return 1;
    number = arg[0] - '0';
    if(number == 0 || number == 1 || number == 2)
        return number;
    else return -1;
}
/*              END OF FILE HW#2                                             */
