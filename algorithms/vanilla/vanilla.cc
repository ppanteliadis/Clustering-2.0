#include "vanilla.hh"

Vanilla::Vanilla() {

}


Vanilla::Vanilla(Data* object) {
	SetData(object);
}


int Vanilla::AssignPointsToCenters() {
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

/**
 *
 */
int Vanilla::start() {
	//GetData()->InitializeClusterCentersRandomly(GetData()->GetCentersSize());
	AssignPointsToCenters();

	return 0;
}


Vanilla::~Vanilla() {

}