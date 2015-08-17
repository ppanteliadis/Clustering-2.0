#ifndef ALGORITHM_HH
#define ALGORITHM_HH


#include "data.hh"


class Algorithm {
private:
	Data* data;
	long int iterations;

public:
	Algorithm();
	Algorithm(Data*);
	~Algorithm();

	int start(void);

	Data* GetData(void);
	long int GetIterations();

	void SetData(Data*);
	void SetIterations(long int);
};

#endif