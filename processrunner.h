#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;

struct Process {
    string name = "uninit";
    int start = 0;
    int duration = 0;
    bool complete = false;
    bool ready = false;
    int runtime = 0;
    string history;
};

class ProcessRunner {
    public:
        ProcessRunner(vector<Process*> new_p);
        ~ProcessRunner();
        void addTime();
        bool done() {return is_done;};
        int time() {return current_time;};
        vector<Process*> processes;
    private:
        Process* current_process;
        list<Process*> waiting;
        bool is_done;
        int current_time;
};