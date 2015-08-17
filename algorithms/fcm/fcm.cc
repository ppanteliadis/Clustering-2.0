#include "fcm.hh"

Fcm::Fcm() {

}


Fcm::Fcm(Data* object) {
	SetData(object);
}

/**
 * @param			point 				The point to which the membership is needed.
 * @param			center 				The center to which the membership is needed.
 * @return 								Returns the new value for U_ij (aka membership).
 * @brief								Calculates and returns the degree of membership for a given point and a center.
 */
float Fcm::GetNewValue(int point, int center) {

	float t, p, sum;
	sum = 0;
	p = 2 / (GetData()->GetFuzziness() - 1);

	for (int i = 0; i < GetData()->GetCentersSize(); ++i) {
		t = GetData()->GetDistanceBetweenPointAndCenter(point, center) / GetData()->GetDistanceBetweenPointAndCenter(point, i);
		t = pow(t, p);
		sum += t;
	}

	return 1/sum;
}



/**
 * @return 								Returns the max difference.
 * @brief 								Updates the degree of membership for every point and returns the max difference found.
 */
float Fcm::UpdateDegreeOfMembership(void) {

	float new_uij, difference;
	float max_difference = 0;

	long int iterations = 0;

	for (int i = 0; i < GetData()->GetCentersSize(); ++i) {
		for (int j = 0; j < GetData()->GetPointsSize(); ++j) {
			new_uij = GetNewValue(j, i);
			
			difference = new_uij - GetData()->GetDegreeOfMembership(j, i);
			//difference = new_uij - degree_of_membership[j][i];

			if (difference > max_difference) {
				max_difference = difference;
			}

			GetData()->SetDegreeOfMembership(j, i, new_uij);
			//degree_of_membership[j][i] = new_uij;

			iterations++;
		}
	}

	SetIterations(iterations);

	return max_difference;
}


/**
 * @return 								Returns 0 if all goes well.
 * @brief 								Computes the Fuzzy c-means algorithm.
 */
int Fcm::start() {
	GetData()->InitializeDegreesOfMembership();
	float max_difference;
	do {
		GetData()->CalculateClusterCenters();
		max_difference = UpdateDegreeOfMembership();
	} while (max_difference > GetData()->GetEpsilon());

	return 0;
}


Fcm::~Fcm() {
	
}