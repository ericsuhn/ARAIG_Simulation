#ifndef _ARAIG_SENSOR_H_
#define _ARAIG_SENSOR_H_

#include "Task.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>


namespace ms{

	class ARAIG_Sensor {
		vector<Stimulation*> v_stimulations;
		vector<Task*> v_tasks;
		int num_stimulations;

	public:
		ARAIG_Sensor(std::string, std::string);			//constructor
		Location to_enum(string);						//converts a string to an enum
		~ARAIG_Sensor();
		ostream& dump(ostream&);
		Task operator[](size_t x){ return *v_tasks[x]; } //overloads [] operator
		int getSize(){ return v_tasks.size(); }			 //return size of v_tasks

	};

}


#endif