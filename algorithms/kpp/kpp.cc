#include "kpp.hh"

/* Global vars*/
float glbl_D_x = -1;
float glbl_D_x_sqrd = -1;
float glbl_max_D_x_sqrd = -1; 				//distances can't be negatives.
float glbl_point_with_max_d_x = -1;
float glbl_point_with_max_d_x_sqrd = -1;
int glbl_closest_center = -1;


Kpp::Kpp() {


}

Kpp::Kpp(Data* object) {
	SetData(object);
}

/**
 *
 */
int Kpp::start() {
	CarefullSeeding(GetData()->GetCentersSize());
	AssignPointsToCenters();
	return 0;
}


/**
 *
 */
int Kpp::GetClosestClusterCenter(int point) {
	int min_index = 0;
	double minimum_distance = -1;
	int cc_size = GetData()->GetCentersSize();

	for (int i = 0; i < cc_size-1; ++i) {

		double dist = GetData()->GetDistanceBetweenPoints(point, i);
		if (minimum_distance > dist && dist != 0) {
			minimum_distance = dist;
			min_index = i;
		}
	}
	return min_index;
}


/**
 *
 */
int Kpp::FlipACoin(float probability) {
	srand(time(NULL));
	double p = ((double)rand() / RAND_MAX);
	//heads.
	if (p <= probability) {
		return 0;
	}
	else { //tails.
		return 1;
	}
}


/**
 *
 */
int Kpp::EasyApproximationOfCenters(int point) {

	if (glbl_D_x_sqrd > glbl_max_D_x_sqrd) {
		glbl_max_D_x_sqrd = glbl_D_x_sqrd;
		glbl_point_with_max_d_x = point;
	}
	return 0;
}


/**
 *
 */
int Kpp::DifficultApproximationOfCenters(float* array, int sum) {
	for (int i = 0; i < GetData()->GetPointsSize(); ++i) {

		float probability = array[i] / sum;
		int coin = FlipACoin(probability); /* heads = 0, tails = 0. */
		if (coin == 0) {
			glbl_point_with_max_d_x = i;
		}
		else {
			EasyApproximationOfCenters(i);
		}
	}
	return 0;
}


/**
 *
 */
int Kpp::CarefullSeeding(int point) {
	//initializing 1st center at random.
	srand(time(NULL));
	//set cc[0] = ...
	int first_center  = rand() % GetData()->GetPointsSize();
	long int iterations = 0;

	GetData()->AddClusterCenters(first_center);

	float* D_x_array = new float[GetData()->GetPointsSize()];
	float sum_D_x_sqrd = -1;

	//until K centers have been chosen.
	for (int i = 1; i < GetData()->GetCentersSize(); ++i) {
		//for each data point x.
		glbl_point_with_max_d_x_sqrd = 0;
		sum_D_x_sqrd = -1;

		//iterate threw the data_points.
		for (int j = 0; j < GetData()->GetPointsSize(); ++j) {
			//find the closest cluster center.
			glbl_closest_center = GetClosestClusterCenter(j);

			//compute D(x) dist between x and nearest center already chosen.
			glbl_D_x = GetData()->GetDistanceBetweenPointAndCenter(j, glbl_closest_center);
			glbl_D_x_sqrd = pow(glbl_D_x, 2);

			//1. Start of easy approximation of center. Point with max (D(x))^2, will be center.
			EasyApproximationOfCenters(j);
			// End of easy approximation. Uncomment this and comment the other implementation to avoid Seg Faults!

			//2.a Start of Difficult, more costly, but more efficient approximation of center.
			//Initialize some values. The sum of ALL D(x)^2 and an array of size N containing all
			//and for each point, have it's corresponding D(x)^2 in an array. 
			D_x_array[j] = glbl_D_x_sqrd;
			sum_D_x_sqrd += glbl_D_x_sqrd;
			iterations++;
		}

		//2.b Approximating 1 center at a time by flipping a coin.
		DifficultApproximationOfCenters(D_x_array, sum_D_x_sqrd);

		GetData()->AddClusterCenters(glbl_point_with_max_d_x); 
	}

	//SetIterations(iterations);
	delete D_x_array;

	return 0;
}


int Kpp::AssignPointsToCenters() {
	int k = GetData()->GetCentersSize();
	int n = GetData()->GetPointsSize();
	long int iterations = 0;

	float point_to_center_dist1 = std::numeric_limits<double>::infinity();

	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < n; ++j) {
			point_to_center_dist1 = GetData()->GetDistanceBetweenPointAndCenter(j, i);

			//Checking the points distance to the center.
			if (GetData()->GetMinimumDistance(j) > point_to_center_dist1 
				&& GetData()->GetMinimumDistance(j) != 0) {

				GetData()->SetMinimumDistance(j, point_to_center_dist1);
				GetData()->SetCenterPointer(j, i);
			}
			iterations++;
		}
	}

	SetIterations(iterations);
	return 0;
}





Kpp::~Kpp() {


}
