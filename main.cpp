#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "processrunner.h"
#include <getopt.h>
#include <sstream>

using namespace std;

vector<Process*> randprocesses(int amt) 
{
    vector<Process*> processes;
    for(int i = 0; i < amt; ++i) {
        Process* p = new Process;
        p->name = "rand" + to_string(i);
        p->start = rand() % 30;
        p->duration = (rand() % 40);
        ++p->duration;
        cout << "Created process " << p->name << ": starts at " << p->start <<", duration " << p->duration << endl;
        processes.push_back(p);
    }
    cin.get();
    return processes;
}

//Give it a name and a vector of processes to hurl the processes into.
void readFile(string filename, vector<Process*> &addTo){
	string line;
	ifstream pfile;
	pfile.open(filename);
	while(getline(pfile, line)){
          cout << "Reading process from line " << line << endl;
          stringstream ss;
          ss << line;
          Process* p = new Process;
          string name;
          int start, duration;
          ss >> name >> start >> duration;
          p->name = name;
          p->start = start;
          p->duration = duration;
          addTo.push_back(p);
	}
        pfile.close();
}

//below macro ripped shamelessly from https://cfengine.com/blog/2021/optional-arguments-with-getopt-long/
//For some reason, getopt_long(), when given the optional_argument flag, expects the optional arg like this:
//
//-fcfsMYARGUMENT
//
//No idea why. Convenience macro so I don't have to write it repeatedly.

#define OPTARG_IS_PRESENT \
  ((optarg == NULL && optind < argc && argv[optind][0] != '-') \
   ? (bool)(optarg = argv[optind++]) \
     : (optarg != NULL))

const struct option long_options[] = {
  {"r", required_argument, 0, 'r'},
  {"fcfs", optional_argument, 0, 'a'},
  {"rr", optional_argument, 0, 'b'},
  {"hrrn", optional_argument, 0, 'c'},
  {"sjf", optional_argument, 0, 'd'},
  {"sjr", optional_argument, 0, 'e'},
};

int main(int argc, char** argv)
{
  int index;
  int iarg = 0;
  opterr = 1;
  vector<Process*> processes;
  //In each case you just set scheduler to one of the inherited classes of Scheduler.
  //scheduler = new RRScheduler(processes);
  //for round robin.
  Scheduler* scheduler = nullptr;
  while(iarg != -1) {
    iarg = getopt_long_only(argc, argv, "r:a::b::c::d::e::", long_options, &index);
    switch(iarg) {
      case 'r':
        {
          vector<Process*> randproc = randprocesses(stoi(optarg));
          processes.insert(processes.end(), randproc.begin(), randproc.end());
          break;
        }
      case 'a'://FCFS
        {
          cout << "FCFS algorithm selected." << endl;
          if(OPTARG_IS_PRESENT) {
            cout << "Included file." << endl;
            readFile(optarg, processes);
          }
          scheduler = new Scheduler(processes);
          break;
        }
      case 'b': //Round Robin
        {
          if(OPTARG_IS_PRESENT) {
            readFile(optarg, processes);
          }
          scheduler = new RRScheduler(processes);
          break;
        }
      case 'c': //HRRN
        {
          if(OPTARG_IS_PRESENT) {
            readFile(optarg, processes);
          }
          scheduler = new HRRNScheduler(processes);
          break;
        }
      case 'd': //SJF
        {
          if(OPTARG_IS_PRESENT) {
            readFile(optarg, processes);
          }
          scheduler = new SJFScheduler(processes);
          break;
        }
      case 'e': //SJR
        {
          if(OPTARG_IS_PRESENT) {
            readFile(optarg, processes);
          }
          scheduler = new SJRScheduler(processes);
          break;
        }
    }
  }
  if(processes.size() == 0) {
    cout << "No file selected / no rand flag set. Defaulting to 5 random processes." << endl;
    vector<Process*> randproc = randprocesses(5);
    processes.insert(processes.end(), randproc.begin(), randproc.end());
  }
  if(scheduler == nullptr) {
    cout << "No algorithm selected. Defaulting to FCFS. " << endl;
    scheduler = new Scheduler(processes);
  }
  while(!scheduler->done()) {
    scheduler->tick();
  }
  double avg = 0;
  int totalwait = 0;

  for(int i = 0; i < processes[0]->history.size(); ++i) {
    cout << i;
    if(i < 10) cout << "     ";
    else if(i >= 10 && i < 100) cout << "    ";
    else if(i >= 100 && i < 1000) cout << "   ";
    else cout << "  ";

    for(Process* p : processes) {
      cout << p->history[i] << " ";
    }
    cout << endl;
  }

  for(Process* p : processes) {
    totalwait += p->waittime;
  }
  cout << "Makespan: " << scheduler->time() << " ticks." << endl;
  delete scheduler;
  return 0;
}
