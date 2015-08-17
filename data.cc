#include "data.hh"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

Data::Data(){

}


/*Misc Functions*/

/**
 *
 */
vector<string>& Data::divide(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


/**
 *
 *//**
 *
 */
vector<string> Data::divide(const string &s, char delim) {
	vector<string> elems;
	divide(s, delim, elems);
	return elems;
}


/**
 *
 */
int Data::LoadData(string file_name, int data_size, int input_dim) {
	data_points = new DataPoint[data_size];

	SetPointsSize(data_size);

	data_points_size = data_size;

	SetDimension(input_dim);
	//dimension = input_dim;

	string line;
	ifstream my_file (file_name);

	int posn = 0;
	int dim;

	if (my_file.is_open()) {
		while ( getline (my_file,line,';') && data_size != 0) {

			vector <string> items = divide(line,',');

			data_points[posn].values = new DataType[input_dim];
			//data_points[posn].values = new DataType[input_dim];
			data_size--;

			dim = 0;
			assert(items.size() <= (unsigned)input_dim);

			for (int i = 0; i < input_dim; ++i) {
				GetPoint(posn).values[dim] = stof(items[i]);
				//SetDimension(GetDimension() + 1);
				dim++;
			}

			data_points[posn].center = NULL; //check again on Hierarchical Clustering.
			data_points[posn].minimum_distance = std::numeric_limits<double>::infinity();
			data_points[posn].accessed = false;

			posn++;
		}
	}
	else {
		cout << "Unable to open file"; 
	}

	my_file.close();
	return 0;
}


/**
 *
 */
int Data::LoadData(string file_name, int data_size, int input_dim, char mode) {
	/* Points */
	data_points = new DataPoint[data_size];
	data_points_size = data_size;
	dimension = input_dim;

	/* Cluster Centers*/
	InitializeClusterCenters(data_size);
	
	string line;
	ifstream my_file (file_name);

	int posn = 0;
	int dim;
	
	if (my_file.is_open()) {
		while ( getline (my_file,line,';') && data_size != 0) {

			vector <string> items = divide(line,',');
			data_points[posn].values = new DataType[input_dim];
			data_points[posn].minimum_distance = std::numeric_limits<double>::infinity();
			data_size--;
			dim = 0;
			assert(items.size() <= (unsigned)input_dim);
			for (int i = 0; i < input_dim; ++i){
				data_points[posn].values[dim] = stof(items[i]);
				dim++;
			}
			data_points[posn].accessed = false;

			//create the points corresponding cluster center and point to the center.
			AddClusterCenters(posn);
			data_points[posn].center = &cluster_centers->centers[posn];

			posn++;
		}
	}
	else {
		cout << "Unable to open file";
	}
	my_file.close();
	return 0;
}


/**
 * @param 			cc_size 			The size of the Centers.
 * @return 								Returns 0 if all is well.
 * @brief 								Allocates memory for the Cluster Centers. 
 */
int Data::InitializeClusterCenters(int cc_size) {

	cluster_centers = new ClusterCenters();
	cluster_centers->centers = new DataPoint[cc_size];
	SetCentersSize(cc_size);
	return 0;
}


/**
 * @param 			cc_size 			The size of the Centers.
 * @return 								Returns 0 if all is well.
 * @brief 								Allocates memory for the Cluster Centers and randomly initializes it
 */
int Data::InitializeClusterCentersRandomly(int cc_size) {

	cluster_centers = new ClusterCenters();
	SetCentersSize(cc_size);
	cluster_centers->centers = new DataPoint[cc_size];
	srand(time(NULL));

	for (int i = 0; i < cc_size; ++i) {
		int position = rand() % GetPointsSize();
		AddClusterCenters(position);
	}

	return 0;
}


/**
 * @param			position 			The data point position.
 * @return 								Returns 0 if all is well.
 * @brief								Sets a new Cluster Center in the specified position.
 */
int Data::AddClusterCenters(int position) {

	assert(position<data_points_size);

	cluster_centers->centers[cluster_centers->current_position] = data_points[position];
	cluster_centers->current_position++;

	return 0;
}


/**
 * @return 								Returns 0 if all is well.
 * @brief								Set's the centers for Fuzzy C-Means.
 */
int Data::CalculateClusterCenters() {

	//float t[data_points_size][cluster_centers->cluster_centers_size];
	float num, denom;
	float** t = new float*[data_points_size];

	for (int i = 0; i < data_points_size; ++i) {
		t[i] = new float[cluster_centers->cluster_centers_size];
		for (int j = 0; j < cluster_centers->cluster_centers_size; ++j) {
			t[i][j] = pow(degree_of_membership[i][j], fuzziness);
		}
	}

	for (int i = 0; i < cluster_centers->cluster_centers_size; ++i) {
		cluster_centers->centers[i].values = new DataType[dimension];
		for (int j = 0; j < dimension; ++j) {
			num = 0;
			denom = 0;
			for (int k = 0; k < data_points_size; ++k) {
				num += t[k][i] * data_points[k].values[j];
				denom += t[k][i];
			}
			cluster_centers->centers[i].values[j] = num / denom;
		}
	}

	return 0;
}


/**
 *
 */
float Data::GetDistanceBetweenPoints(int point1, int point2) {
	assert(point1 < GetPointsSize());
	assert(point2 < GetPointsSize());

	float sum = 0;

	for (int i = 0; i < GetDimension(); ++i) {
		sum += pow(data_points[point1].values[i] - data_points[point2].values[i], 2);
	}

	return sqrt(sum);
}


/**
 *
 */
float Data::GetDistanceBetweenCenters(int center1, int center2) {
	if (cluster_centers->centers[center1].accessed == true || cluster_centers->centers[center2].accessed == true) {
		return 0;
	}

	float sum = 0;
	for (int i = 0; i < GetDimension(); ++i) {
		sum += pow(cluster_centers->centers[center1].values[i] - cluster_centers->centers[center2].values[i], 2);
	}
	return sqrt(sum);
}


/**
 *
 */
float Data::GetDistanceBetweenPointAndCenter(int point, int center) {
	float sum = 0;

	for (int i = 0; i < GetDimension(); ++i) {
		sum += pow(data_points[point].values[i] - cluster_centers->centers[center].values[i], 2);
	}

	return sqrt(sum);
}


/**
 *
 */
DataPoint& Data::GetPoint(int position) {
	assert(position < data_points_size);
	return data_points[position];
}


/**
 *
 */
DataPoint& Data::GetCenter(int position) {
	//assert(position < cluster_centers->cluster_centers_size);
	return cluster_centers->centers[position];
}

bool Data::GetAccessed(int position) {
	return data_points[position].accessed;
}

float Data::GetMinimumDistance(int position) {
	return data_points[position].minimum_distance;
}


/**
 *
 */
void Data::SetPoint(int position, DataPoint point) {

}


/**
 *
 */
void Data::SetCenter(int position, DataPoint point) {

}

void Data::SetCenterPointer(int point, int center) {
	data_points[point].center = &cluster_centers->centers[center];
}


void Data::SetAccessed(int position, bool _accessed){
	data_points[position].accessed = _accessed;
}

void Data::SetMinimumDistance(int position, float _distance) {
	data_points[position].minimum_distance = _distance;
}

/**
 *
 */
int Data::GetDimension() {
	return dimension;
}


/**
 *
 */
int Data::GetPointsSize() {
	return data_points_size;
}


/**
 *
 */
int Data::GetCentersSize() {
	return cluster_centers->cluster_centers_size;
}


/**
 *
 */
float Data::GetEpsilon() {
	return epsilon;
}


/**
 *
 */
float Data::GetFuzziness() {
	return fuzziness;
}



/**
 *
 */
void Data::SetDimension(int _dimension) {
	dimension = _dimension;
}



/**
 *
 */
void Data::SetPointsSize(int _size) {
	data_points_size = _size;
}


/**
 *
 */
void Data::SetCentersSize(int _size) {
	cluster_centers->cluster_centers_size = _size;
}



/**
 *
 */
void Data::SetEpsilon(float _epsilon) {
	epsilon = _epsilon;
}



/**
 *
 */
void Data::SetFuzziness(float _fuzziness) {
	fuzziness = _fuzziness;
}



/**
 * @return 								Return 0 if all is well.
 * @brief 								Initializes the degrees of memberships array.
 */
int Data::InitializeDegreesOfMembership() {
	double sum;
	int r, rval;
	degree_of_membership = new float*[GetPointsSize()];
	for (int i = 0; i < GetPointsSize(); ++i) {
		sum = 0;
		r = 100;
		degree_of_membership[i] = new float[GetCentersSize()];
		for (int j = 1; j < GetCentersSize(); ++j) {
			rval = rand() % (r+1);
			r -= rval;
			SetDegreeOfMembership(i, j, rval/100);
			//degree_of_membership[i][j] = rval / 100;
			sum += GetDegreeOfMembership(i, j);
			//sum += degree_of_membership[i][j];
		}
		SetDegreeOfMembership(i, 0, 1 - sum);
		//degree_of_membership[i][0] = 1 - sum;
	}
	return 0;
}



/**
 *
 */
float Data::GetDegreeOfMembership(int i, int j) {
	return degree_of_membership[i][j];
}



/**
 *
 */
void Data::SetDegreeOfMembership(int i, int j, float _value) {
	degree_of_membership[i][j] = _value;
}


/**
 *
 */
int Data::FuseCenters(int center1, int center2) {
	if (cluster_centers->centers[center1].accessed == false &&
		cluster_centers->centers[center2].accessed == false) {
		
		//calculate coordinates for new center.
		for (int i = 0; i < GetDimension(); ++i) {
			cluster_centers->centers[center1].values[i] = (float)((cluster_centers->centers[center1].values[i] + cluster_centers->centers[center2].values[i]) / 2);
		}

		//Assign the second center to the first.
		cluster_centers->centers[center2].center = &cluster_centers->centers[center1];

		//"delete" second center.
		cluster_centers->centers[center2].accessed = true;

	}
	return 0;
}



/**
 *
 */
int Data::PrintData(void) {
	for (int i = 0; i < GetPointsSize(); ++i) {
		for (int j = 0; j < GetDimension(); ++j){
			cout<<GetPoint(i).values[j]<<"\t";
		}
		cout<<endl;
	}
	return 0;
}


Data::~Data(){

}