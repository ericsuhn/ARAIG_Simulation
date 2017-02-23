#include "Exoskeleton.h"


namespace ms {

	Exoskeleton::Exoskeleton(){
		intensity = 0;
		duration = 0;
	}

	Exoskeleton::Exoskeleton(string name_, int intensity_, int duration_){
		name = name_;
		intensity = intensity_;
		duration = duration_;
	}

	void Exoskeleton::display(std::ostream& os) const{

		os << name << endl;
		os << setfill(' ') << setw(5) << " ";
		os << "Type = Exoskeleton" << endl;
		os << setfill(' ') << setw(5) << " ";
		os << "Intensity = " << intensity << endl;
		os << setfill(' ') << setw(5) << " ";
		os << "Duration = " << duration << endl;

	}

	string Exoskeleton::getName() const{
		return name;
	}


}