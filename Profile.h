#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "Task.h"
#include "ARAIG_Sensors.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

namespace ms {
	//holds profile Min and Max intensity
	struct min_max_intensity{
		int min;
		int max;
	};

	class Profile{
		/*Profile information*/
		string student_firstName;			
		string student_lastName;
		int student_number;
		string instructor_firstName;
		string instructor_lastName;
		int employee_number;
		min_max_intensity mM_intensity;
		/*Vectors holding Completed tasks and tasks that are in queue to be run.*/
		vector<Task*>toRun;
		vector<Task*>Completed;

	public:
		~Profile();
		Profile(std::string, ostream&, ARAIG_Sensor&);
		ostream& displayToRun(ostream&);
		ostream& displayCompleted(ostream&);
		ostream& printCompletedDetail(ostream&);
		ostream& displayNextTask(ostream&);
		ostream& displayLastTask(ostream&);
		void run();
	};

}

#endif