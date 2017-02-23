#ifndef _TASKS_H_
#define _TASKS_H_

#include "Stimulation.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include <list>
#include <algorithm>
#include <fstream>
#include <memory>


namespace ms{

	class Task {
		string task_name; //holds Task name.
		std::list<Stimulation*> l_stimulations; //holds a list of Stimulations

	public:
		Task();										/*constructors*/
		Task(std::string);
		Task(std::string t_name, list<Stimulation*> ls);
		~Task();									//destructor
		Task(Task&);								//copy constructor
		Task& operator=(const Task&);				//copy operator
		Task(Task&&);								//move constructor
		Task&& operator=(Task&&);					//move operator
		void operator+=(Stimulation*);				//+= operator to add Simulations object using +=
		Stimulation& operator[](size_t) const;			//overload [], allows to index stimulations
		void removeStimulation(string);				//remove a stimulation based on stimulation name.
		ostream& dump(ostream&);					//outputs stim names
		ostream& execute(ostream&);					//displays details of each stimulation object to the ostream& provided.
		string getName() const{ return task_name; }	//returns task name string.		
	};

}

#endif