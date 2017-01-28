/*
	This header simulate c++ map class
*/
#ifndef KEYC_H
#define KEYC_H
#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
#include <string>
using namespace std;

template<class T>
class KeyC
{
public:    
    KeyC(){ number = 0; }
    KeyC(T var1, T var2):KeyC()
    {
        this->first = var1;
        this->second = var2;
    }

    KeyC(const KeyC& var)
    {
        this->first=var.first;
        this->second=var.second;
        this->number = var.number;
        this->dataType = var.dataType;
    }
    KeyC& operator=(const KeyC& other) {
        this->first = other.first;
        this->second = other.second;
        this->number = other.number;
        this->dataType = other.dataType;
        
        return *this; 
    };

    const T getFirst() const {return first;}
    const T getSecond() const {return second;}
    const int getNumber() const {return number;}
    const int getDataType() const { return dataType;}
    
    const void setKeys(const T var1, const T var2)  { first = var1; second = var2;}
    const void setNumber(const int num) { number = num; }
    const void setDataType(const int dType) { dataType = dType; }
    const void setFirstSecond( T var1,  T var2) { first = var1; second = var2; }
protected:
    T first, second; //key1 and key2
    int number; // number of occurance of key pairs
    int dataType; //means 1 for int, 2 for strings, 3 for doubles   
};

#endif /* KEYC_H */

