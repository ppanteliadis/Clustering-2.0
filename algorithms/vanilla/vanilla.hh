#ifndef VANILLA_HH
#define VANILLA_HH

#include "../../algorithm.hh"

class Vanilla : public Algorithm {


private:

public:
	Vanilla();
	Vanilla(Data*);
	~Vanilla();

	int AssignPointsToCenters();
	int start();
};


#endif