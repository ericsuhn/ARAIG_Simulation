#include "Stims.h"

namespace ms {

	Stims::Stims(){

		name = "";
		location = Location::undefined;
		intensity = 0;
		frequency = 0;
		duration = 0;
	}

	Stims::Stims(string name_, Location location_, int intensity_, int frequency_, int duration_){

		name = name_;
		location = location_;
		intensity = intensity_;
		frequency = frequency_;
		duration = duration_;
	}

	void Stims::display(std::ostream& os) const{

		/*enum Location{ abs = 0, front, back, traps, "undefined" }*/
		const char* location_txt[5] = { "abs", "front", "back", "traps", "undefined" };

		os << name << endl;
		os << setfill(' ') << setw(5) << " ";
		os << "Type = Stim" << endl;
		os << setfill(' ') << setw(5) << " ";
		os << setw(5) << "Location = " << location_txt[location] << endl;
		os << setfill(' ') << setw(5) << " ";
		os << setw(5) << "Intensity = " << intensity << endl;
		os << setfill(' ') << setw(5) << " ";
		os << setw(5) << "Frequency = " << frequency << endl;
		os << setfill(' ') << setw(5) << " ";
		os << setw(5) << "Duration = " << duration << endl;
	}

}




