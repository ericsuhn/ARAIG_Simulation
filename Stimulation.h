#ifndef _STIMULATION_H
#define _STIMULATION_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
//Parent class of Stims and Exoskeleton class
class Stimulation
{
protected:
	string name;

public:

	virtual void display(std::ostream&) const = 0;
	string getName() const { return name; }
	virtual Stimulation* clone() const = 0;

};


#endif