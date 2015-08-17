#ifndef KPP_HH
#define KPP_HH

#include "../vanilla/vanilla.hh"

/* Global vars*/
extern float glbl_D_x;
extern float glbl_D_x_sqrd;
extern float glbl_max_D_x_sqrd;
extern float glbl_point_with_max_d_x;
extern float glbl_point_with_max_d_x_sqrd;
extern int glbl_closest_center;


class Kpp : public Algorithm {

private:
	int GetClosestClusterCenter(int);
	int FlipACoin(float);
	int EasyApproximationOfCenters(int);
	int DifficultApproximationOfCenters(float*, int);
	int CarefullSeeding(int);
	int AssignPointsToCenters();


public:
	Kpp();
	Kpp(Data*);
	~Kpp();

	int start();
};

#endif