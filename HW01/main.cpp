/*
    GEBZE TECHNICAL UNIVERSITY
    CSE241 HW#1
    MUHAMMED SELIM DURSUN
    1301044023 
 
    Program that will simulate a very simple CPU. CPU has only 5 registers
    (R1, R2, R3, R4, R5) and no other memory.
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct MovAddSub
{
    bool probability1 ; //if true mean that MOV reg, reg
    bool probability2 ; //if true mean that MOV reg, constant
    int registerNumber1, registerNumber2; // if need, registerNumber2 using  
    int constant ;
} MovAddSub_t;

typedef struct prn
{
    bool probability1 ; //if true mean that PRN reg
    bool probability2 ; //if true mean that PRN constant 
    int registerNumber;
    int constant;
}prn_t;

typedef struct jmp
{
    bool probability1 ; //if true mean that JMP reg, lineadress
    bool probability2 ; //if true mean that JMP lineadress
    int registerNumber;
    int lineadress;
}jmp_t;

/*
 * if previous process read JMP, this function do control remain of string
 * Ex; JMP R1, 10 >>> if R1 is 0, jump 10. line else next line
 * EX; JMP 10 >>> unconditional jump 10. line
 * @param1 data, parsing string that after part of instruction
 * @param2 jmp, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int jmpControl(string data, jmp_t &jmp, bool &END);

//init jmp structure element
void initJmp(jmp_t &jmp);

/*
 * Print value of register or constant
 * Ex: PRN R1 >>> print value of R1
 * Ex: PRN 10 >>> print 10
 * @param1 data, parsing string that after part of instruction
 * @param2 prn, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int PrnControl(string data, prn_t &prn, bool &END);

//init prn structure element
void initPrn(prn_t &prn);

/*
 * Read file, changing string. if any chars lower case, convert to upper case
 * Update number of the filled line of string array
 */
void readFileAndFillDataArray(fstream *inp, string *data, int *num );

//init registers to 0
void initRegisters(int *R,int size);

//if there any lower case char, converting to uppercase
void uppercaseConverter(string &buffer);

//string simplification as per following conditions
string editSpacesAndTabs(string line);

/*
 * Read instructions and call related function, and moves to next line
 * @param1 *data >> string array, max line numbers 200
 * @param2 R >> symbolize registers that R1,R2,R3,R4,R5
 * @param3 option >> work kind of debugger, if option 1, print all operations
 * @param4 maxData >> size of string array
 */
void fileProcess(string *data, int R[], int option, int maxData );

/* if return -1, not match.
 * @param1 string, output parameter. new string after parsing
 * @param2 buffer, output parameter. parsed parameter
 * @param3 delim, delimeters.
 */
int cStrTok(string &strng, string &buffer, char delim);

/*
 * if previous process read MOV or ADD or SUB, 
 * this function do control remain of string
 * Instructions(MOV,ADD,SUB) contents is same
 * Instruction reg, reg
 * Instruction reg, constant
 * @param1 data, parsing string that after part of instruction
 * @param2 var, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int MovAddSubControl(string data, MovAddSub_t &var, bool &END);

//init AddMovSub structure element
void initInstructionVars(MovAddSub_t &var);

//convert string to integer. arg must be 1 or 0, else return -1 (error)
int stringToInteger(string arg);


int main(int argc, char** argv) {  
    const int registerNums = 5;
    const int maxData = 200;
    int option;
    string data[maxData];
    int number = 0; //line numbers of text file

    fstream inp;
    // represent registers, R[0]=R1, R[1]=R2, R[2]=R3, R[3]=R4, R[4]=R5
    int R[registerNums]; 
    
    if(argc != 3)
    {
    	cout << "missing or too argument" << endl;
    	return -1;
    }
    option = stringToInteger(argv[2]);
    if(option == -1)
    {
        cout << "Invalid option !" << endl;
        return -1;
    }
    
    initRegisters(R, registerNums);   
    
    inp.open(argv[1]);

    if (!inp.is_open()){
        cout << "can't open the file" << endl;
        return -1;
    }

    readFileAndFillDataArray(&inp, data, &number); 
    fileProcess(data, R, option, maxData);        
    inp.close();
    
    return 0;
}  
/*
 * Read instructions and call related function, and moves to next line
 * @param1 *data >> string array, max line numbers 200
 * @param2 R >> symbolize registers that R1,R2,R3,R4,R5
 * @param3 option >> work kind of debugger, if option 1, print all operations
 * @param4 maxData >> size of string array
 */
void fileProcess(string *data, int R[], int option, int maxData )
{
    //Structures variables
    MovAddSub_t var;
    prn_t prn;
    jmp_t jmp;
    
    int line = 0; //current line number
    int opLine; //previous line number
    //manupulation strings
    string buffer;
    string buffer2;
    int indicator = 0; // return value control variable
    bool END = false; // if END true, process will end
    
    //init structures
    initInstructionVars(var);
    initPrn(prn);
    initJmp(jmp);
    
    while(!END)
    {
        buffer2 = data[line];
        opLine = line;
        indicator = cStrTok(buffer2, buffer, ' '); //parsing
        //buffer must equal to instructions
        if(indicator != -1)
        {
            if(buffer == "MOV")
            {            
                if(!MovAddSubControl(buffer2, var, END))
                {
                    if(var.probability1)
                    {   
                        R[var.registerNumber1 - 1] = R[var.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(var.probability2)
                    {   
                        R[var.registerNumber1 - 1] = var.constant;
                        line += 1;
                    }
                    if(option)
                    {
                        cout << data[opLine] << "- R1=" << R[0] << ", R2=" ;
                        cout<< R[1] << ", R3=" << R[2] << ", R4=" << R[3] ;
                        cout << ", R5=" << R[4]<<endl ; 
                    }
                    initInstructionVars(var);
                }          
            }
            else if(buffer == "ADD")
            {
                if(!MovAddSubControl(buffer2, var, END))
                {
                    if(var.probability1)
                    {
                        R[var.registerNumber1 - 1] += R[var.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(var.probability2)
                    {
                        R[var.registerNumber1 - 1] += var.constant;
                        line += 1;
                    }
                    if(option)
                    {
                        cout << data[opLine] << "- R1=" << R[0] << ", R2=" ;
                        cout<< R[1] << ", R3=" << R[2] << ", R4=" << R[3] ;
                        cout << ", R5=" << R[4]<<endl ; 
                    }
                    initInstructionVars(var);
                }
            }
            else if(buffer == "SUB")
            {
                if(!MovAddSubControl(buffer2, var, END))
                {
                    if(var.probability1)
                    { 
                        R[var.registerNumber1 - 1] -= R[var.registerNumber2 - 1];
                        line += 1;
                    }
                    else if(var.probability2)
                    { 
                        R[var.registerNumber1 - 1] -= var.constant;
                        line += 1; 
                    }
                    if(option)
                    {
                        cout << data[opLine] << "- R1=" << R[0] << ", R2=" ;
                        cout<< R[1] << ", R3=" << R[2] << ", R4=" << R[3] ;
                        cout << ", R5=" << R[4]<<endl ; 
                    }
                    initInstructionVars(var);
                }
            }
            else if(buffer == "PRN")
            {
                if(!PrnControl(buffer2, prn,END))
                {
                    if(prn.probability1)
                    {
                        cout << "Value of R" << prn.registerNumber ;
                        cout << " is " << R[prn.registerNumber-1] << endl;
                        line += 1;
                    }
                    else if(prn.probability2)
                    {
                        cout << "Constan value is " << prn.constant << endl;
                        line += 1;
                    }
                    if(option)
                    {
                        cout << data[opLine] << "- R1=" << R[0] << ", R2=" ;
                        cout<< R[1] << ", R3=" << R[2] << ", R4=" << R[3] ;
                        cout << ", R5=" << R[4]<<endl ; 
                    }     
                    initPrn(prn);
                }
            }
            else if(buffer == "JMP")
            {
                
                if(!jmpControl(buffer2, jmp, END))
                {
                	if( jmp.lineadress - 1 < maxData)
                	{
		                if(jmp.probability1)
		                { 
		                    if(R[jmp.registerNumber-1] == 0)
		                    {
		                        line = jmp.lineadress - 1;
		                    }
		                    else
		                        line +=1;
		                }
		                else if(jmp.probability2)
		                {
		                    line = jmp.lineadress - 1;
		                }
		                if(option)
		                {
		                    cout << data[opLine] << "- R1=" << R[0] << ", R2=" ;
		                    cout<< R[1] << ", R3=" << R[2] << ", R4=" << R[3] ;
		                    cout << ", R5=" << R[4]<<endl ; 
		                }
		                initJmp(jmp);
                    }
                    else
                    {
		                if(END!=true)
		                    cout << "Segmentation Fault!"  << endl;
		                END = true;
                    }
                }
                else
                {
                    if(END!=true)
                        cout << "Syntax Error!" << endl;
                    END = true; 
                }
            }
            else if(buffer == "HLT")
            {   
                if(buffer2 == "\0")
                    END = true;
                else
                {
                    if(END!=true)
                        cout << "Syntax Error!" << endl;
                    END = true;
                }
            }
            else
            {
                if(END!=true)
                        cout << "Syntax Error!" << endl;
                END=true;
            }
        }
        else
        {
            if(END!=true)
                cout << "Syntax Error!"<<endl;
            END=true;
        }
    }
}
/*
 * if previous process read JMP, this function do control remain of string
 * Ex; JMP R1, 10 >>> if R1 is 0, jump 10. line else next line
 * EX; JMP 10 >>> unconditional jump 10. line
 * @param1 data, parsing string that after part of instruction
 * @param2 jmp, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int jmpControl(string data, jmp_t &jmp, bool &END)
{
    int j;
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool isConstantPositive = true;
    
    buffer2 = data;
    
    indicator = cStrTok(data, buffer, ',');
    if(indicator != -1)
    {  
        jmp.probability1=true;
        if(buffer.size() == 2 && buffer[0] == 'R')
        {
            if(buffer[1] >= 49 && buffer[1] <= 53 )
            {
                jmp.registerNumber = buffer[1] - '0'; 
            }
            else
            {
                if(END!=true)
                    cout << "Syntax Error!"<<endl;
                END = true;
                return -1;
            }
        }
        else
        {
            if(END!=true)
                cout << "Syntax Error!"<<endl;
            END = true;
            return -1;
        }
        j=0;
        indicator = cStrTok(data, buffer, ' ');
        if(buffer[0] == '-')
        {
            j=1;
            isConstantPositive = false;
        }
        for(int i = j; i < buffer.size(); ++i)
        {
            if(buffer[i] >= 48 && buffer[i] <= 57)
            {   
                jmp.lineadress *= 10;                            
                jmp.lineadress += buffer[i] - '0';
            }
            else
            {
                if(END!=true)
                    cout << "Syntax Error!" << endl;
               END = true;
               return -1;
            }
        }
        if(!isConstantPositive) jmp.lineadress *= -1;
        if(jmp.lineadress < 0)
        {
            if(END!=true)   
                cout << "Logical Error, lineadress must be positive." << endl;
            END = true;
            return -1;
        }
    }
    else
    {
        jmp.probability2 = true;
        j=0;
        indicator=cStrTok(buffer2, buffer, ' '); //parsing
        if(indicator == -1)
        {
            if(END!=true)   
                cout << "Syntax Error!" << endl;
            END = true;
            return -1;
        }
        if(buffer[0] == '-')
        {
            j=1;
            isConstantPositive = false;
        }
        for(int i = j; i < buffer.size(); ++i)
        {        

            if(buffer[i] >= 48 && buffer[i] <= 57)
            {           

                jmp.lineadress *= 10;                            
                jmp.lineadress += buffer[i] - '0';
            }
            else
            {
                if(END!=true)
                    cout << "Syntax Error!"<<endl;
                END = true;
                return -1;
            }
        }
        if(!isConstantPositive) jmp.lineadress *= -1;
        
        if(jmp.lineadress < 0)
        {
            if(END!=true)
                cout << "Logical Error, lineadress must be positive." << endl;
            END = true;            
            return -1;
        }
        
        if(buffer2[0] != '\0')
        {   
            if(END!=true)
                cout << "Syntax Error!"<<endl;
            END = true;
            return -1;
        }
    }

    return 0;
}
/*
 * Print value of register or constant
 * Ex: PRN R1 >>> print value of R1
 * Ex: PRN 10 >>> print 10
 * @param1 data, parsing string that after part of instruction
 * @param2 prn, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int PrnControl(string data, prn_t &prn, bool &END)
{
    string buffer, buffer2;  //manupulation strings
    bool isConstantPositive = true;
        
    buffer2 = data;
    buffer2.erase(buffer2.size()-1);

    cStrTok(data, buffer, ' ');

    if(buffer2 != buffer)
    {
        if(END!=true)
            cout << "Syntax Error!"<<endl;
        END = true;
        return -1;
    }
    if(buffer == "R1" || buffer == "R2" || buffer == "R3" || 
           buffer == "R4" || buffer == "R5"  )
    {
        prn.registerNumber = buffer[1] - '0';
        prn.probability1 = true;
    }
    else if(buffer[0] == 'R')
    {
        if(END!=true)
            cout << "Syntax Error!"<<endl;
        END = true;
        return -1 ;
    }
    else
    {
        int j=0;
        prn.probability2 = true;
        if(buffer[0] == '-')
        {
            j=1;
            isConstantPositive = false;
        }
        for(int i = j; i < buffer.size(); ++i)
        {
            if(buffer[i] >= 48 && buffer[i] <= 57)
            {   
                prn.constant *= 10;                            
                prn.constant += buffer[i] - '0';
            }
            else
            {
                if(END!=true)
                    cout << "Syntax Error!" << endl;
                END = true;
                return -1;
            }
        }
        if(!isConstantPositive) prn.constant *= -1;
    }
    return 0;
}
/*
 * if previous process read MOV or ADD or SUB, 
 * this function do control remain of string
 * Instructions(MOV,ADD,SUB) contents is same
 * Instruction reg, reg
 * Instruction reg, constant
 * @param1 data, parsing string that after part of instruction
 * @param2 var, structure parameter
 * @param3 END, if value true, all process is over
 * 
 * On error return -1, else return 0
 */
int MovAddSubControl(string data, MovAddSub_t &var, bool &END)
{
    string buffer, buffer2;  //manupulation strings
    int indicator=0; // function return value control variable.
    bool isConstantPositive = true;
    indicator = cStrTok(data, buffer, ',');
    
    if(indicator != -1)
    {
        if(buffer == "R1" || buffer == "R2" || buffer == "R3" || 
           buffer == "R4" || buffer == "R5"  )
        {
            var.registerNumber1 = buffer[1] - '0';
        }
        else
        {
            if(END!=true)
                cout << "Syntax Error!"<<endl;
            END = true;
            return -1;
        }
        buffer2 = data;
        buffer2.erase(buffer2.size()-1);  
        indicator = cStrTok(data, buffer, ' ');   
        if(buffer2 != buffer)
        {
            if(END!=true)
                cout << "Syntax Error!" << endl;
            END = true;
            return -1;
        }

        if(buffer == "R1" || buffer == "R2" || buffer == "R3" || 
           buffer == "R4" || buffer == "R5"  )
        {
            var.registerNumber2 = buffer[1] - '0';
            var.probability1 = true;
        }
        else if(buffer[0] == 'R')
        {
            if(END!=true)
                cout << "Syntax Error!" << endl;
            END = true;
            return -1 ;
        }
        else
        {
            int j=0;
            var.probability2 = true;
            if(buffer[0] == '-')
            {
                j=1;
                isConstantPositive = false;
                if(buffer[1] < 48 || buffer[1] > 57)
                {
                    if(END!=true)
                        cout << "Syntax Error!" << endl;
                    END = true;
                    return -1;
                }
            }
            else if(buffer[0] < 48 || buffer[0] > 57)
            {
                if(END!=true)
                    cout << "Syntax Error!" << endl;
                END = true;
                return -1;
            }
      
            for(int i = j; i < buffer.size(); ++i)
            {
                if(buffer[i] >= 48 && buffer[i] <= 57)
                {   
                    var.constant *= 10;                            
                    var.constant += buffer[i] - '0';
                }
                else
                {
                    if(END!=true)
                        cout << "Syntax Error!" << endl;
                    END = true;
                    return -1;
                }
            }

            if(!isConstantPositive) var.constant *= -1;
        }
    }
    else
    {
        if(END!=true)
             cout << "Syntax Error!" << endl;
        END = true;
        return -1;
    }
    
    
    return 0;
}
//init MovAddSub structure element
void initInstructionVars(MovAddSub_t &var)
{
    var.probability1 = false;
    var.probability2 = false;
    var.registerNumber1 = 0;
    var.registerNumber2 = 0;
    var.constant = 0;
}
//init prn structure element
void initPrn(prn_t &prn)
{
    prn.probability1 = false;
    prn.probability2 = false;
    prn.registerNumber = 0;
    prn.constant = 0;
}
//init jmp structure element
void initJmp(jmp_t &jmp)
{
    jmp.probability1 = false;
    jmp.probability2 = false;
    jmp.registerNumber = 0;
    jmp.lineadress = 0;
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

//init registers to 0
void initRegisters(int *R, int size)
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


//string simplification as per following conditions
string editSpacesAndTabs(string line)
{   
    int i, number;
    string buffer;
    
    //deleting head spaces
    for(int i=0; i<line.size();++i)
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
//convert string to integer. arg must be 1 or 0, else return -1 (error)
int stringToInteger(string arg)
{
    int number;
    if(arg.size() != 1)
        return 1;
    number = arg[0] - '0';
    if(number == 1 || number == 0)
        return number;
    else return -1;
}

/*              END OF FILE HW#1                                             */
