#include "ARAIG_Sensors.h"
#include "Stimulation.h"


namespace ms{

	ARAIG_Sensor::ARAIG_Sensor(std::string StimConfig, std::string TaskConfig){

		num_stimulations = 0;
		std::ifstream file;
		/*open StimConfig(throw exception)*/
		try {
			file.open(StimConfig);
			if (!file.is_open()){
				throw "File could not be openned.";
			}
		}
		catch (const char* msg) {
			v_stimulations.clear();
			cout << msg << std::endl;
		}

		while (file.good()){
			
			std::string type, s_name, s_location;
			unsigned s_intensity, s_frequency, s_duration;
			
			/*Read Stimulation information*/
			std::getline(file, type, ',');
			std::getline(file, s_name, ',');

			std::transform(type.begin(), type.end(), type.begin(), ::tolower);

			/*If stim, read stim information and create stim object*/
			if (type == "stim"){
				std::getline(file, s_location, ',');
				Location location = to_enum(s_location);
				file >> s_intensity;
				file.ignore(2000, ',');
				file >> s_frequency;
				file.ignore(2000, ',');
				file >> s_duration;
				file.ignore(2000, '\n');
				v_stimulations.push_back(new Stims(s_name, location, s_intensity, s_frequency, s_duration));
				num_stimulations++;
			}
			/*If exoskeleton, read exo information and create exo object*/
			else if (type == "exoskeleton"){
				file >> s_intensity;
				file.ignore(2000, ',');
				file >> s_duration;
				file.ignore(2000, '\n');
				v_stimulations.push_back(new Exoskeleton(s_name, s_intensity, s_duration));
				num_stimulations++;
			}

		}

		/*close StimConfig file*/
		file.close();


		/* Open TaskConfiguration file(throw exception)*/
		try {
			file.open(TaskConfig);
			if (!file.is_open()){
				throw "File could not be openned.";
			}
		}
		catch (const char* msg) {
			cout << msg << std::endl;
		}

		string line, str, task_name, stim_name;
		list<Stimulation*> temp_stimulations;

		while (!file.eof()){
			/*Read Task configuration file lines. Throw error if Line doesnt start with "TASK" OR "Sim" */
			/*Throws error if Sim name does not match StimConfig file*/
				while (getline(file, line, '\n')){

					if (line.substr(0,4) != "TASK" && line.substr(0,3) != "Sim"){
						throw "****Error**** Task Configuration file: Line does not begin with TASK or Sim.";
						continue;
					}
					/*Get Task name from line and put into task_name variable*/
					if (line.substr(0, 4) == "TASK"){
						str = line.substr(5, '\n');
						task_name = str;
						
					}
					/*Get Sim name from line and put into stim_name variable*/
					else if (line.substr(0,3) == "Sim"){
						str = line.substr(0, '\n');
						stim_name = str;
					}
					/*Match stim_name variable with stim from v_stimulations and push into temp list*/
					for (auto it = v_stimulations.begin(); it != v_stimulations.end(); it++){

						if ((*it)->getName() == stim_name){
							temp_stimulations.push_back((std::move(*it)));
							stim_name = "";
						}
					}
					/*This exception returns an error message if Sim number in TaskConfig doesnt match
					any Sim number in Stim config*/
					if (stim_name != ""){
						throw "****Error**** Task Configuration: Sim number does not exist. ";
				
					}
					/*When there are no more Sim lines, create a task object with the temp list of
					Stimulations and push that object into v_tasks (our vector of tasks). Then clears the
					temporary list of stimulations in order to read the next Task*/
					if (file.peek() == 'T' || file.eof()){
						v_tasks.push_back(new Task(task_name, temp_stimulations));
						temp_stimulations.clear();
					}
				}
			}
		
			file.close();

	}

		ARAIG_Sensor::~ARAIG_Sensor(){

			for (vector<Task*>::const_iterator it = v_tasks.begin(); it != v_tasks.end(); it++)
			{
				delete *it;
			}
			v_tasks.clear();

			for (vector<Stimulation*>::const_iterator it = v_stimulations.begin(); it != v_stimulations.end(); it++)
			{
				delete *it;
			}
			v_stimulations.clear();
		}

/*This function outputs all tasks saved in the v_tasks variable*/
		ostream& ARAIG_Sensor::dump(ostream& os){ 

			for (auto it = v_tasks.begin(); it != v_tasks.end(); it++)
			{
				(*it)->dump(os);

			}
			return os;
		}

/*This function converts a string to a location enum*/
		Location ARAIG_Sensor::to_enum(string str){
			
			Location location;

			if (str == "abs"){
				location = abs;
			}
			else if (str == "front"){
				location = front;
			}
			else if (str == "back"){
				location = back;
			}
			else if (str == "traps"){
				location = traps;
			}
			else
				location = undefined;

			return location;
		}

	}