#include "Task.h"



namespace ms{
	/*Default Constructor*/
	Task::Task(){

		task_name = "";
		l_stimulations.clear();
	}
	/*One argument constructor*/
	Task::Task(std::string t_name){

		task_name = t_name;

	}
	/*Two argument constructor*/
	Task::Task(std::string t_name, list<Stimulation*> ls){

		task_name = t_name;
		l_stimulations = ls;

	}

	/*Copy operator*/
	Task::Task(Task& src){

		task_name = "";
		l_stimulations.clear();
		*this = src;

	}

	/*Copy assignment operator*/
	Task& Task::operator=(const Task& src){

		if (this != &src){
			while (!l_stimulations.empty()) delete l_stimulations.front(), l_stimulations.pop_front();
			l_stimulations.clear();
			l_stimulations = src.l_stimulations;
			task_name = src.task_name;
		}

		return *this;
	}
	/*Move operator*/
	Task::Task(Task&& src){

		task_name = src.task_name;
		l_stimulations = src.l_stimulations;
		src.task_name = "";
		src.l_stimulations.clear();

	}
	/*Move assignment operator*/
	Task&& Task::operator = (Task&& src){

		if (this != &src){
            while (!l_stimulations.empty()) delete l_stimulations.front(), l_stimulations.pop_front();
			task_name = src.task_name;
			l_stimulations = src.l_stimulations;
			src.task_name = "";
			src.l_stimulations.clear();
		}
		return std::move(*this);
	}

	Task:: ~Task(){
		l_stimulations.clear();
	}

	void Task::operator+=(Stimulation* s){
		l_stimulations.push_back(s);
	}

	Stimulation& Task::operator[](size_t i) const {

		Stimulation* stim = nullptr;
		size_t count = 0;
		/*iterate through list of stims until index is found, returns stim*/
		for (auto it = l_stimulations.begin(); it != l_stimulations.end(); it++){
			if (i == count){
				stim = *it;
			}
			count++;
		}
			return *stim;
		}

	void Task::removeStimulation(string stim_str){
		/*Removes a stimulation from Task, passes in a string for stim name*/
		if (!l_stimulations.empty()){

			std::list<Stimulation*>::iterator it = l_stimulations.begin();
			/*Iterates through list of stimulations and looks for stim_str. Delete if found.*/
			while (it != l_stimulations.end()){
				string n = (*it)->getName();

				if (n == stim_str){
					it = l_stimulations.erase(it); //erase function automatically goes to next iterator if found (++it)
				}
				else{
					++it;
				}
			}

		}
	}
	/*Display Task names */
	ostream& Task::dump(ostream& os){
		os << "TASK " << task_name << endl;
		for (std::list<Stimulation*>::iterator it = l_stimulations.begin(); it != l_stimulations.end(); ++it)
		{
			os << (*it)->getName() << endl;
		}
		return os;
	}
	/*Display stim information*/
	ostream& Task::execute(ostream& os){

		for (std::list<Stimulation*>::iterator it = l_stimulations.begin(); it != l_stimulations.end(); ++it)
		{
			(*it)->display(os);
		}
		return os;
	}

}
