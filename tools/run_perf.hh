
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>

using namespace std;

void* status;

class perfProfiler{
    
private:
    string events;
    void runPerf();
    int perf_id;
    bool power;
public:
    perfProfiler(string e,bool p);
    void startPerf();
    void endPerf();
};



perfProfiler::perfProfiler(string e, bool p) {
    events = e;
    power = p;
}


void perfProfiler::runPerf() {
    
    int perf_pid = getppid();
    char perf_pid_opt[9];
    snprintf(perf_pid_opt, 24, "%d", perf_pid);
    const char *perfargs_system[8] = {"perf", "stat", "-a", "-x,", "-e",
        events.c_str(), NULL, NULL};
    
    const char *perfargs[9] = {"perf", "stat", "-x,", "-e",
        events.c_str(), "-p",
        perf_pid_opt, NULL, NULL};
    //char *perfargs[6] = {"perf", "stat" ,"-x,", "-e",
    //  	events};
    //if (power)
    //char *perfargs[6] = {"perf", "stat", "-a" ,"-x,", "-e",
    //	events};
    if (power)
        execvp("perf", (char* const*)perfargs_system);
    else
        execvp("perf", (char* const*)perfargs);

    assert(0 && "perf failed to start");
}


/**
 *	Use this function to fork a process that runs perf and attaches it to
 *	the current process.
 */
void perfProfiler::startPerf() {
    int pid = fork();
    
    if(pid>0){
        perf_id = pid;
        return;
    }else if(pid == 0){
        runPerf();
    }
    return;
}


/**
 *	Use this function to stop profiling using perf
 */
void perfProfiler::endPerf() {
    int status = 0;
    kill(perf_id, SIGINT);
    wait(&status);
}
