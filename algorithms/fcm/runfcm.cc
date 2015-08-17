
#include "../../data.hh"
#include "../../algorithm.hh"

//#include "../../tools/run_perf.hh"
//#include "../../tools/timer.hh"

#include "fcm.hh"


bool getParam(int argc, char** argv, int* dataSize, int* clusterCenters, int* dimensions, string* testFile, double* fuzz, double* epsilon){

	int c;
	while ((c = getopt (argc, argv, "n:k:d:t:e:f:")) != -1)
		switch (c){
			case 'n':
				*dataSize = atoi(optarg);
				break;
			case 'k':
				*clusterCenters = atoi(optarg);
				break;
			case 'd':
				*dimensions = atoi(optarg);
				break;
			case 't':
				*testFile = string(optarg);
				break;
			case 'e':
				*epsilon = atof(optarg);
				break;
			case 'f':
				*fuzz = atof(optarg);
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}
	return true;
}




int main(int argc, char* argv[]) {
	cout<<endl<<endl<<endl;

	if (argc == 13) {
		int points_number, attempted_clusters, dims;
		double fuzziness, e;
		string test_file_name;

		getParam(argc, argv, &points_number, &attempted_clusters, &dims, &test_file_name, &fuzziness, &e);

		//timer* t = new timer();
		//perfProfiler* p = new perfProfiler("cycles,cache-misses", false);

		Data* d = new Data();

		//t->start();
		//p->startPerf();

		d->LoadData(test_file_name, points_number, dims);

		d->SetEpsilon(e);
		d->SetFuzziness(fuzziness);
		d->InitializeClusterCenters(attempted_clusters);

		Algorithm* alg = new Algorithm();
		//alg->SetData(d);

		Fcm* fcm = new Fcm(d);

		fcm->start();
		//t->end();
		//p->endPerf();

		cout<<"\nTotal Iterations: "<<fcm->iterations<<endl;
		//cout<<"Total Running time: "<<t->getDiff()<<" seconds."<<endl;
	}
	else {
		cout<<"Wrong argument count."<<endl;
		exit(1);
	}
	return 0;
}