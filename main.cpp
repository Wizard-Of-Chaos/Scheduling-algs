#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "processrunner.h"
#include <getopt.h>
#include <unistd.h>

using namespace std;

const struct option long_options[] = {
	{"roundrobin", no_argument, 0, 'a'},
	{"random", required_argument, 0, 'b'},
};

vector<Process*> randprocesses() 
{
    vector<Process*> processes;
    for(int i = 0; i < 5; ++i) {
        Process* p = new Process;
        p->name = "rand" + to_string(i);
        p->start = rand() % 30;
        p->duration = rand() % 40 + 2;
        cout << "Created process " << p->name << ": starts at " << p->start <<", duration " << p->duration << endl;
        processes.push_back(p);
    }
    cin.get();
    return processes;
}

vector<Process*> readFile(string filename){
	string line;
	vector<Process*> processList;
	ifstream pfile;
	pfile.open(filename);
	while(getline(pfile, line)){
		//add processes from file into the processList
		cout << line; //testing reading from file
	}
}

int main(int argc, char** argv)
{
	/*cout << argv[1];
	if(string(argv[1]) == "-r"){
		Scheduler scheduler(randprocesses());
		while(!scheduler.done()) {
			scheduler.tick();
		}

		for(Process* p : scheduler.processes) {
			cout << "Process " << p->name << ": " << p->history << endl;
		}
		cout << "Total time: " << scheduler.time() << " ticks." << endl;

		return 0;
	}

	if(argv[1] != NULL){
		//read from file
		vector<Process*> processes = readFile(string(argv[1]));
	}*/

	int index;
	int iarg = 0;
	opterr = 1; // stops errors
	while(iarg != -1){
		iarg = getopt_long(argc, argv, "b:a", long_options, &index); 
		//the string in there is just the accepted args from the struct earlier;
		//the colon say it needs an argument
		switch(iarg){
			case 'a':
				//round robin
				cout << "round robin" << endl;
				break;
			case 'b':
				int amount_of_threads = atoi(optarg);
				break;
		}
	}
		 
    return 0;
}
