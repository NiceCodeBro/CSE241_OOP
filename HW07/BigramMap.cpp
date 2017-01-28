#include "BigramMap.h"
using namespace std;
//read file, check error case and throw exceptions for that and fill map
template<typename T>
const void BigramMap<T>::readFile(const string fileName) throw (Exception)
{
    fstream inp;
    inp.open(fileName);
    
    if (!inp.is_open())
    {
        throw Exception("Can't open the file !");
    }
    
    if(checkBadData(inp) == -1)
    {
        throw Exception("Bad data error!");
    }
    if(count<=1)
    {
		throw Exception("File has insufficient staff!");
    }
    inp.close();
    
    inp.open(fileName);
    
    T temp, temp2;
    pair<T, T> pairTemp, pairTemp2;
    
    inp>>temp;
    while(inp>>temp2)
    {   
        pairTemp = make_pair(temp,temp2);
        ++mymap[pairTemp];
        temp=temp2;
    }
    
    inp.close();
}
template<typename T>
void BigramMap<T>::print(ostream& out) const
{
//map copied to template arrays and int array
//sorted arrays by int array and print arrays
	T tempArr1[mymap.size()];
	T tempArr2[mymap.size()];
	
	int counter[mymap.size()] ;
	int a=0;
	typename map< pair<T, T>, int > ::const_iterator iter2;

    for(int i = 0; i < mymap.size(); ++i) counter[i] = 0;
    
    for(iter2=mymap.begin(); iter2!=mymap.end();++iter2)
    {
		tempArr1[a] = (iter2->first).first;
		tempArr2[a] = (iter2->first).second;
		counter[a] = iter2->second;
		++a;
	}
	
    for(int i = 0; i < a - 1; i++)
    {
        for(int j = i + 1; j < a; j++)
        {
            if( counter[i] < counter[j] )
            {
                T tempVar1 = tempArr1[i];
                T tempVar2 = tempArr2[i];
                int tempCount = counter[i];
                
                tempArr1[i] = tempArr1[j];
                tempArr2[i] = tempArr2[j];
                counter[i] = counter[j];
                
                tempArr1[j] = tempVar1;
                tempArr2[j] = tempVar2;
                counter[j] = tempCount;
                
            }
        }
    }
    
    for(int i=0; i < a; ++i)
    {
		out << "[" << tempArr1[i] << ", " << tempArr2[i] << "] = " << counter[i] ;
		if(i < a-1 ) out << endl;
    }

}
//function check if string only contain numbers, convert integer
template<typename T>
const int BigramMap<T>::stringToInteger(const string var) const
{
   
    int number=0;
    
    for(int i=0; i < var.size(); ++i)
    {
        if(var[i]>='0' && var[i]<='9')
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
const double BigramMap<T>::stringToDouble(const string var) const
{
    int indicator=0;

    for(int i=0; i < var.size(); ++i)
    {
        if((var[i]>='0' && var[i]<='9') || var[i]=='.')
        {
            if(var[i]=='.' && i!=var.size()-1 && var[0]!='.') ++indicator;
        }
        else 
            return -1;
    }
    if(indicator!=1) return -1; //string contain more than one dot
    
    return atof(var.c_str());
}
//check @param1 contain only chars else return -1
template<typename T>
const int BigramMap<T>::checkString(const string var) const
{
    for(int i=0; i<var.size(); ++i)
    {
        if(!(var[i]>=65 && var[i]<=90) && !(var[i]>=97 && var[i]<=122))
            return -1;
    }
    return 0;
}
//if read word equal int or double or string, Then others words should be equal to it
template<typename T>
const int BigramMap<T>::checkBadData(fstream &inp) 
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

//returns the total number of bigrams calculated so far.
template<typename T>
const int BigramMap<T>::numGrams() const 
{
    return count-1;
}
//takes two elements as bigrams and returns the number of that bigram read so far.
template<typename T>
const int BigramMap<T>::numOfGrams( T var1,  T var2) const 
{
    pair<T, T> temp;
    typename map< pair<T, T>, int > ::const_iterator iter;

    temp = make_pair(var1,var2);
    iter= mymap.find(temp);
  
    if(iter!=end(mymap))
		return iter->second;
    else 
    	return 0;
    
}
//returns the bigram that has occurred most frequently.
template<typename T>
const pair<T,T> BigramMap<T>::maxGrams() const 
{
    int counter=0;
    int max=0;
    T var1, var2;
    typename map< pair<T, T>, int > ::const_iterator iter;
    pair<T, T> temp;
        
    for(iter=mymap.begin(); iter!=mymap.end();++iter)
    {
        if(iter->second > max)
        {
            temp=iter->first;
            var1=temp.first;
            var2=temp.second;
            max=iter->second;
        }
    }
    return make_pair(var1,var2);   
    // hic yoksa ??? exception
}
