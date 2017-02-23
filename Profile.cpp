#include "Profile.h"



namespace ms{

	Profile::Profile(string filename, ostream& os, ARAIG_Sensor& as){

		std::ifstream file;
		//open file
		try {
			file.open(filename);
			if (!file.is_open()){
				throw "File could not be openned.";
			}
		}
		catch (const char* msg) {
			cout << msg << std::endl;
		}
			string line;
			/*Get Student and Instructor information from file */
			std::getline(file, student_firstName, ',');
			std::getline(file, student_lastName, ',');
			file >> student_number;
			file.ignore(2000, '\n');
			std::getline(file, instructor_firstName, ',');
			std::getline(file, instructor_lastName, ',');
			file >> employee_number;
			file.ignore(2000, '\n');
			/*Get Min and Max values from file */
			file >> mM_intensity.max;
			file.ignore(2000, ',');
			file >> mM_intensity.min;

			
			os << "Student: " << student_firstName << " " << student_lastName <<
				" - " << student_number << endl;
			os << "Instructor: " << instructor_firstName << " " << instructor_lastName <<
				" - " << employee_number << endl;
			os << "Student Calibration: " << endl;
			os << "MAX = " << mM_intensity.max << endl;
			os << "MIN = " << mM_intensity.min << endl;
			file.ignore(2000, '\n');

			string _task;
			/*Read Tasks from profile configuration file*/
			while (getline(file, _task, '\n')){
				for (int it = 0; it < as.getSize(); it++){
					if (as[it].getName() == _task){
						toRun.push_back(new Task(as[it]));
					}
				}
			}
		file.close();
		
	}
	/*List of Tasks in queue to be run*/
	ostream& Profile::displayToRun(ostream& os){
		os << endl;
		os << "Tasks to run: \n";
		os << "____________________\n\n";
		for (auto it = toRun.begin(); it < toRun.end(); ++it){
			os << (*it)->getName() << endl;
		}
		return os;
	}

	/*Displays task names of tasks completed*/
	ostream& Profile::displayCompleted(ostream& os){
		
		os << endl;
		os << "Tasks completed: \n";
		os << "____________________\n\n";
		for (auto it = Completed.begin(); it < Completed.end(); ++it){
			os << (*it)->getName() << endl;
		}
		os << endl;

		return os;
	}
	/*Lists detailed completed Tasks, writes to outputfile*/
	ostream& Profile::printCompletedDetail(ostream& os){
		for (auto it = Completed.begin(); it < Completed.end(); ++it){
			os << (*it)->getName() << endl;
			Completed.back()->execute(os);
		}
		return os;
	}
	
	
	ostream& Profile::displayNextTask(ostream& os){

		os << toRun.back()->getName();
		return os;
	}

	ostream& Profile::displayLastTask(ostream& os){

		os << Completed.back()->getName();
		return os;
	}
	
	void Profile::run(){

			cout << "Welcome to ARAIG. The Profile information you have entered has loaded successfully. \n\n";
			char key = ' ';

			while (!toRun.empty() && key!= 'x') {

				if (!Completed.empty()){
					cout << "The last task you executed was ";
					displayLastTask(cout) << ".\n";
				}
				cout << "The next task to execute is ";
				displayNextTask(cout) << ".\n\n";
				cout << "Input [n] to execute next task in the list." << endl;
				cout << "Input [l] to see the list of tasks to be executed." << endl;
				cout << "Input [k] to see the list of tasks that have already been executed." << endl;
				cout << "Input [x] to exit" << endl << endl;
				
				cin.get(key);
				cin.ignore(2000, '\n');
				cout << endl;

				switch (key){
				case 'n':
					/*Displays the name of the Task being executed*/
					cout << toRun.back()->getName() << endl;
					/*Displays the details of each Stimulation object*/
					toRun.back()->execute(cout);
					/*Move task to completed vector*/
					Completed.push_back(std::move(toRun.back()));
					toRun.pop_back();
					cout << endl;
					break;
				case 'l':
					displayToRun(cout);
					cout << endl;
					break;
				case 'k':
					displayCompleted(cout);
					break;
				case 'x':
					break;
				default:
					cout << "Invalid input." << endl;
					break;
					
				}

			}

	}

	Profile::~Profile(){

		for (vector<Task*>::const_iterator it = toRun.begin(); it != toRun.end(); it++)
		{
			delete *it;
		}
		toRun.clear();

		for (vector<Task*>::const_iterator it = Completed.begin(); it != Completed.end(); it++)
		{
			delete *it;
		}
		Completed.clear();
	}

}