/*
	this header for throw exception
*/

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class Exception: public runtime_error
{
public:
	Exception():runtime_error("") {}
	Exception(string var) :except(var), runtime_error(var){}
	string what() { return except; }
private:
	string except;
};

#endif /* EXCEPTION_H */
