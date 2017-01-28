/*
The second class is BigramDyn which does not use
any STL classes or STL functions, it uses only old fashioned dynamic memory.

This header simulate that c++ map class using helper Key class
*/
#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
#include <string>
#include "Bigram.h"
#include "KeyC.h"
#include "Exception.h"
using namespace std;

template<typename T>
class BigramDyn:public Bigram<T>
{
public:
    BigramDyn(){count = 0; keyUsed = 0;  key = new KeyC<T>[1];  }
    BigramDyn(const int datatype):BigramDyn(){ dataType = datatype; key = new KeyC<T>[1]; } 

	virtual ~BigramDyn() { delete [] key; }
	virtual void print(ostream& out) const;
    //function check if string only contain numbers, convert integer
    const int stringToInteger(const string var) const;
    //check @param1 contain only double else return -1
    const double stringToDouble(const string var) const;
    //check @param1 contain only chars else return -1
    const int checkString(const string var) const;   
    //if read word equal int or double or string, Then others words should be equal to it
    const int checkBadData(fstream &inp);  
	/*check our dynamic map exist pair(var1 and var2),if exist increase that index counter
	if not exist, add pair to end of key,sort by number of pair by decreasing order*/
    const int editKeyClassArray(const T var1,const T var2, int &loopVar);
    //read file, check error case and throw exceptions for that and fill key class array
    virtual const void readFile(const string fileName) throw (Exception) override ;
    //returns the total number of bigrams calculated so far.
    virtual const int numGrams() const override;
    //takes two elements as bigrams and returns the number of that bigram read so far.
    virtual const int numOfGrams(T var1,  T var2) const override;
    //returns the bigram that has occurred most frequently.
    virtual const pair<T,T> maxGrams() const override;
    const int getCount() const { return count; }
    const int getKeyUsed() const { return keyUsed; }
    const KeyC<T> getKey(const int index) const { return key[index]; }
    const int getDataType() const { return dataType; }
protected:
    int count; //number of element from file (123 3244 22 means count = 3)
    int dataType; //means 1 for int, 2 for strings, 3 for doubles
    int keyUsed;
    KeyC<T>* key;
};

#endif /* BIGRAMDYN_H */
