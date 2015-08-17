
#include "../../data.hh"
#include "../../algorithm.hh"

//#include "../../tools/run_perf.hh"
//#include "../../tools/timer.hh"

#include "hierarchical.hh"


bool getParam(int argc, char** argv, int* dataSize, int* dimensions, string* testFile){

	int c;
	while ((c = getopt (argc, argv, "n:k:d:t:")) != -1)
		switch (c){
			case 'n':
				*dataSize = atoi(optarg);
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

	if (argc == 7) {
		int N, dims;
		string test_file_name;

		getParam(argc, argv, &N, &dims, &test_file_name);

		//timer* t = new timer();
		//perfProfiler* p = new perfProfiler("cycles,cache-misses", false);

		Data* d = new Data();
		Algorithm* alg = new Algorithm();

		//t->start();
		//p->startPerf();

		d->LoadData(test_file_name, N, dims, 'd');

		Hierarchical* hierarchical = new Hierarchical(d);
		hierarchical->start();

		//t->end();
		//p->endPerf();

		cout<<"Total iterations: "<<hierarchical->GetIterations()<<endl;
		//cout<<"Total Running time: "<<t->getDiff()<<" seconds."<<endl;
	}
	else {
		std::cout<<"Wrong argument count."<<endl;
		exit(1);
	}
	return 0;
}