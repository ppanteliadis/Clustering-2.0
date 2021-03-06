
#include "../../data.hh"
#include "../../algorithm.hh"

//#include "../../tools/run_perf.hh"
//#include "../../tools/timer.hh"

#include "vanilla.hh"


bool getParam(int argc, char** argv, int* dataSize, int* clusterCenters, int* dimensions, string* testFile){

	int c;
	while ((c = getopt (argc, argv, "n:k:d:t:")) != -1)
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

	if (argc == 9) {
		int N, K, dims;
		string test_file_name;

		getParam(argc, argv, &N, &K, &dims, &test_file_name);

		//timer* t = new timer();
		//perfProfiler* p = new perfProfiler("cycles,cache-misses", false);

		Data* d = new Data();
		d->LoadData(test_file_name, N, dims);

		//t->start();
		//p->startPerf();

		d->InitializeClusterCentersRandomly(K);

		Algorithm* alg = new Algorithm();
		Vanilla* vanilla = new Vanilla(d);
		vanilla->start();

		//t->end();
		//p->endPerf();

		cout<<"Total iterations: "<<vanilla->GetIterations()<<"."<<endl;
		//cout<<"Total Running time: "<<t->getDiff()<<" seconds."<<endl;
		return 0;
	}
	else {
		cout<<"Wrong argument count."<<endl;
		exit(1);
	}
}