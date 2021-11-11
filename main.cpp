#include <iostream>
#include <string>
#include <vector>
#include "processrunner.h"

using namespace std;

vector<Process*> randprocesses() 
{
    vector<Process*> processes;
    for(int i = 0; i < 5; ++i) {
        Process* p = new Process;
        p->name = "rand" + to_string(i);
        p->start = rand() % 20;
        p->duration = rand() % 20 + 4;
        cout << "Created process " << p->name << ": starts at " << p->start <<", duration " << p->duration << endl;
        processes.push_back(p);
    }
    cin.get();
    return processes;
}

int main(int argc, char** argv)
{
    ProcessRunner scheduler(randprocesses());

    while(!scheduler.done()) {
        scheduler.addTime();
    }

    for(Process* p : scheduler.processes) {
        cout << "Process " << p->name << ": " << p->history << endl;
    }
    cout << "Total time: " << scheduler.time() << " ticks." << endl;
    return 0;
}