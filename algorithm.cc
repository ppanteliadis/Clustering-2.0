#include "algorithm.hh"


/**
 *
 */
Algorithm::Algorithm() {
	iterations = 0;
}


/**
 *
 */
Algorithm::Algorithm(Data* sData) {
	iterations = 0;
	data = sData;
}


/**
 *
 */
Data* Algorithm::GetData() {
	return data;
}

/**
 *
 */
long int Algorithm::GetIterations() {
	return iterations;
}


/**
 *
 */
int Algorithm::start() {

	return 0;
}


/**
 *
 */
void Algorithm::SetData(Data* _data) {
	data = _data;
}

/**
 *
 */
void Algorithm::SetIterations(long int _iterations) {
	iterations = _iterations;
}


/**
 *
 */
Algorithm::~Algorithm() {
	
}