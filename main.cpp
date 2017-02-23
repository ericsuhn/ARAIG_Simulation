#include "Stimulation.h"
#include "Task.h"
#include "ARAIG_Sensors.h"
#include "Profile.h"
#include <list>



using namespace std;
using namespace ms;

int main(int argc, char* argv[]){

	if (argc != 5) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << "file_name\n";
		return 1;
	}

	std::ofstream ofs(argv[4], std::ofstream::out);

	try{
		//Load Stimulations and Task Objects.
		std::unique_ptr<ARAIG_Sensor> araig(new ARAIG_Sensor(argv[2], argv[3]));

		//Load Profile.
		std::unique_ptr<Profile> profile(new Profile(argv[1], ofs, *araig));

		//Execute the flight plan (Run Tasks), until user finishes or exits.
		profile->run();
		
		//writes completed tasks to file
		profile->printCompletedDetail(ofs) << endl;
		
		cout << "Press any key to exit..." << endl;
		std::cin.get();
	}
	catch (char* err){
		cout << err << endl;
	}

	ofs.close();

	return 0;
}