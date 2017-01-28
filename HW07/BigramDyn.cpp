#include"BigramDyn.h"
#include <iostream>

using namespace std;
//read file, check error case and throw exceptions for that and fill key class array
template<typename T>
const void BigramDyn<T>::readFile(const string fileName)  throw (Exception)
{
    fstream inp;
    inp.open(fileName);
    
    if (!inp.is_open())
    {
       throw Exception("Can't open the file!");
    }
    
    if(checkBadData(inp) == -1)
    {
        throw Exception("Bad data error!");
    }
    if(count <= 1)
    {
        throw Exception("File has insufficient staff!");
    }
    inp.close();
       
    key = new KeyC<T>[count]; // allocating from memory
    for(int i = 0; i < count; ++i)
    {
        key[i].setDataType(dataType);
    }

    inp.open(fileName);
    
    int j = 0;
    T temp, temp2;
    
    inp >> temp;
    while(inp >> temp2)
    {
        if(editKeyClassArray(temp,temp2,j)) 
        	key[j].setFirstSecond(temp, temp2);
        temp = temp2; 
    }
       
    inp.close();    
}
template<typename T>
void BigramDyn<T>::print(ostream& out) const
{
        
    for(int i = 0; i < keyUsed; ++i)
    {
		out << "[" << key[i].getFirst() << ", " << key[i].getSecond() << "] = " << key[i].getNumber();
		if(i!=keyUsed-1) out << endl;
	}
}

//returns the bigram that has occurred most frequently.
template<typename T>
const pair<T,T> BigramDyn<T>::maxGrams() const
{
    pair<T,T> temp;


    temp.first = key[0].getFirst();
    temp.second = key[0].getSecond();
    
    return temp;
}
//returns the total number of bigrams calculated so far.
template<typename T>
const int BigramDyn<T>::numGrams() const
{
    if(this->count != 0)
        return this->count-1;
    else
        return this->count;
}
//takes two elements as bigrams and returns the number of that bigram read so far.
template<typename T>
const int BigramDyn<T>::numOfGrams( T var1,  T var2) const
{
    bool flag = false;
    int index;
    int i;
    for(i = 0; i < this->keyUsed; ++i)
    {
        if(var1 == key[i].getFirst() && var2 == key[i].getSecond() )
        {
            flag = true;
            index = i;
            i = this->keyUsed;
        }
    }
    
    if(flag)
        return key[index].getNumber();
    else
        return 0;
}
/*
	check our dynamic map exist pair(var1 and var2)
	if exist increase that index counter
	if not exist, add pair to end of key 
	sort by number of pair by decreasing order
*/
template<typename T>
const int BigramDyn<T>::editKeyClassArray(const T var1,const T var2, int &loopVar)
{
    bool flag = false;
    int whichIndex = 0;
    for(int i = 0; i < this->keyUsed; ++i)
    {	//check our dynamic map exist pair(var1 and var2)
        if(key[i].getFirst() == var1 && key[i].getSecond() == var2) 
        {
            flag = true; 
            whichIndex = i;
        }
    }
    
    if(flag == true) //if exist increase that index counter
    {
        key[whichIndex].setNumber(key[whichIndex].getNumber() + 1);
    }
    else // if not exist, add pair to end of key 
    {
        key[this->keyUsed].setKeys(var1, var2);
        key[this->keyUsed].setNumber(key[this->keyUsed].getNumber() + 1);
        ++this->keyUsed;
        ++loopVar;
    }
    
    //sort by number of pair by decreasing order
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = i + 1; j < count; j++)
        {
            if(key[i].getNumber() < key[j].getNumber() )
            {
                KeyC<T> tempKey(key[i]);
                key[i] = key[j];
                key[j] = tempKey;
            }
        }
    }
    
    if(flag == false)
        return 1;
    else
        return 0;
}
//if read word equal int or double or string, Then others words should be equal to it
template<typename T>
const int BigramDyn<T>::checkBadData(fstream &inp) 
{ 
    string temp;
    while(inp>>temp)
    {      
        ++count;
     
	    if(getDataType() == 1 && stringToInteger(temp)==-1 )
	    {
	        return -1;
	    }  
	    else if(getDataType() == 3 && stringToDouble(temp)==-1 )
	    {
	        return -1;
	    }     
    }
    return 0;   
}
//function check if string only contain numbers, convert integer
template<typename T>
const int BigramDyn<T>::stringToInteger(const string var) const
{
    int number = 0;
    for(int i = 0; i < var.size(); ++i)
    {
        if(var[i] >= '0' && var[i] <= '9')
        {
            number *= 10;
            number += var[i]-'0';
        }
        else    
            return -1;
    }
    return number;
}
//check @param1 contain only double else return -1
template<typename T>
const double BigramDyn<T>::stringToDouble(const string var) const
{
    int indicator = 0;

    for(int i=0; i < var.size(); ++i)
    {
        if((var[i] >= '0' && var[i] <= '9') || var[i] == '.')
        {
            if(var[i] == '.' && i != var.size()-1 && var[0] != '.') ++indicator;
        }
        else 
            return -1;
    }
    
    if(indicator!=1) return -1; //string contain more than one dot
    
    return atof(var.c_str());
}
//check @param1 contain only chars else return -1
template<typename T>
const int BigramDyn<T>::checkString(const string var) const
{
    for(int i = 0; i < var.size(); ++i)
    {
        if(!(var[i] >= 65 && var[i] <= 90) && !(var[i] >= 97 && var[i] <= 122))
            return -1;
    }
    return 0;
}
