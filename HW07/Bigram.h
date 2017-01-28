/*
	The base class will be Bigram which will have only pure abstract functions 
	and nothing else.
*/

#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
using namespace std;
template <class T>
class Bigram
{
public:
    Bigram(){}
    virtual ~Bigram(){}
    virtual const void readFile(const string fileName) = 0;
    virtual const int numGrams() const=0;
    virtual const int numOfGrams( T num1, T num2) const=0;
    virtual const pair<T,T> maxGrams() const = 0;
    virtual void print(ostream& out) const =0;
    
   	friend ostream& operator <<(ostream& outputStream, const Bigram<T> &dd) {
   		dd.print(outputStream);
   		return outputStream;
   	}    
};

#endif /* BIGRAM_H */

