#ifndef FCM_HH
#define FCM_HH

#include "../../algorithm.hh"


class Fcm : public Algorithm {

private:
	long int iterations;						/* number of total iterations. */

	float GetNewValue(int, int);				/* Calculates and returns the degree of membership for a given point and a center. */
	float UpdateDegreeOfMembership(void);		/* Updates the degree of membership for every point and returns the max difference found. */


public:
	Fcm();
	Fcm(Data*);
	~Fcm();

	int start();


};

#endif