#ifndef _EXOSKELETON_H_
#define _EXOSKELETON_H_

#include "Stimulation.h"


namespace ms {

	class Exoskeleton : public Stimulation
	{
		int intensity;
		int duration;

	public:
		Exoskeleton();
		Exoskeleton(string, int, int);
		void display(std::ostream&) const;
		string getName() const;
		Stimulation* clone() const { return new Exoskeleton(*this); }
	};

}

#endif