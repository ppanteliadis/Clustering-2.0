#ifndef DATA_HH
#define DATA_HH

#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <cfloat>

//#include "./tools/run_perf.hh"
//#include "./tools/timer.hh"



using namespace std;

/*****************************************************
The API to interact with the data set. 
** status load_data(char** filename)
** 
*****************************************************/

/**
 * Data type (FLOAT by default)
 */
typedef float DataType;

/**
 * Data type (FLOAT by default)
 */

/**
 * each point in the data set has a dimension and values.
 */
typedef struct DataPoint {
	DataType* values;
	DataPoint* center;						/* Pointer to the center it corresponds to. */
	bool accessed;							/* If true, point is accessed. */
	float minimum_distance;
}DataPoint;


typedef struct ClusterCenters{
	DataPoint* centers;
	int current_position = 0;
	int cluster_centers_size;
}ClusterCenters;



class Data {

private:
	int dimension;							/* The dimension of each point */
	int data_points_size;					/* Number of data points */
	DataPoint* data_points; 				/* The array of stored data values */
	ClusterCenters* cluster_centers;		/* The cluster centers */

	float epsilon, fuzziness;				/* Termination criterion and fuzziness coefficient */
	float** degree_of_membership;			/* [data_points_size][cluster_centers_size] */

	vector<string>& divide(const string&, char, std::vector<string>&);
	vector<string>divide(const string&, char);


public:
	Data();													/* Constructor */
	~Data();												/* Destructor */

	int LoadData(string, int, int); 						/* Load values from a file */
	int LoadData(string, int, int, char);					/* Hierarchical requires different initialization */
	int InitializeClusterCenters(int);
	int InitializeClusterCentersRandomly(int);
	int AddClusterCenters(int);
	int CalculateClusterCenters(void);						/* Calculate the centers for fcm */

	float GetDistanceBetweenPoints(int, int);
	float GetDistanceBetweenCenters(int, int);
	float GetDistanceBetweenPointAndCenter(int, int);

	int FuseCenters(int, int);

	DataPoint& GetPoint(int);
	DataPoint& GetCenter(int);

	DataPoint& GetCenterPointer();
	bool GetAccessed(int);

	void SetPoint(int, DataPoint);
	void SetCenter(int, DataPoint);

	int GetDimension(void);
	int GetPointsSize(void);
	int GetCentersSize(void);

	float GetEpsilon(void);
	float GetFuzziness(void);
	float GetMinimumDistance(int);


	void SetCenterPointer(int, int);
	void SetAccessed(int, bool);

	void SetDimension(int);
	void SetPointsSize(int);
	void SetCentersSize(int);

	void SetEpsilon(float);
	void SetFuzziness(float);
	void SetMinimumDistance(int, float);

	int InitializeDegreesOfMembership(void);

	float GetDegreeOfMembership(int, int);
	float UpdateDegreeOfMembership(void);
	void SetDegreeOfMembership(int, int, float);

	int PrintData(void);
};

#endif