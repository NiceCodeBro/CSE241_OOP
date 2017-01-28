/*
	 This class uses STL Map class to implement functions. 
	 a class hierarchy for bigrams (2-Gram). A bigram is a specialization 
	 of N-Gram which “is a contiguous sequence of N items from a given data sequence”.
*/
#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <utility>
#include "Bigram.h"
#include "Exception.h"
using namespace std;

template<typename T>
class BigramMap:public Bigram<T>
{
public:
    BigramMap(){count=0;}
    BigramMap(const int datatype):BigramMap(){ dataType = datatype; }
    
    const bool sortMethod (const int i,const int j) const { return (i<j); }
	virtual void print(ostream& out) const;
    //function check if string only contain numbers, convert integer
    const int stringToInteger(const string var) const;
    //check @param1 contain only double else return -1
    const double stringToDouble(const string var) const;
    //check @param1 contain only chars else return -1
    const int checkString(const string var) const;   
    //if read word equal int or double or string, Then others words should be equal to it
    const int checkBadData(fstream &inp) ;
    //read file, check error case and throw exceptions for that and fill map
    virtual const void readFile(const string fileName) throw (Exception) override;
    //returns the total number of bigrams calculated so far.
    virtual const int numGrams() const override;
    //takes two elements as bigrams and returns the number of that bigram read so far.
    virtual const int numOfGrams( T num1,  T num2) const override ;
    //returns the bigram that has occurred most frequently.
    virtual const pair<T,T> maxGrams() const override;
	const int getDataType() const {return dataType; }
protected:
    int dataType; //means 1 for int, 2 for strings, 3 for doubles
    int count; //number of element from file (123 3244 22 means count=3)
    map< pair<T, T>, int > mymap;
};

#endif /* BIGRAMMAP_H */
