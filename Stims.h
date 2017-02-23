#ifndef _STIMS_H_
#define _STIMS_H_

#include "Stimulation.h"
#include "map"

namespace ms {

	enum Location { abs = 0, front, back, traps, undefined};

	class Stims : public Stimulation
	{

		Location location;
		int intensity;
		int frequency;
		int duration;

	public:
		Stims();
		Stims(string, Location, int, int, int);
		void display(std::ostream&) const;
		Stimulation* clone() const { return new Stims(*this); }
	};

}

#endif