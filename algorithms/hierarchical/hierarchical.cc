#include "hierarchical.hh"

Hierarchical::Hierarchical() {

}

Hierarchical::Hierarchical(Data* obj) {
	SetData(obj);
}


/**
 *
 */
int Hierarchical::start() {
	GetData()->SetCentersSize(GetData()->GetPointsSize());

	float distance;
	float minimum;

	bool flag = false;

	int* points = new int[2];
	int iter = 0;

	while (GetData()->GetCentersSize() > 1) {
		for (int i = 0; i < GetData()->GetPointsSize(); ++i) {
			//reset the minimum.
			minimum = FLT_MAX;
			points[0] = i;
			for (int j = i+1; j < GetData()->GetPointsSize(); ++j) {

				distance = GetData()->GetDistanceBetweenCenters(i,j);

				if (distance < minimum && distance != 0) {
					points[1] = j;
					minimum = distance;
					flag = true;
				}
				iter++;
			}
			//now that we have the minimum. Fuse the 2 centers.IF there was a change in the points.
			if (flag == true) {

				GetData()->FuseCenters(points[0], points[1]);

				//reset the flag
				flag = false;

				//reduce centers size.
				GetData()->SetCentersSize(GetData()->GetCentersSize() - 1);
			}
		}
	}

	SetIterations(iter);
	return 0;
}


Hierarchical::~Hierarchical() {
	
}