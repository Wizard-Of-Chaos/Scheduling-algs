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

class Scheduler {
    public:
        Scheduler(vector<Process*> new_p);
        Scheduler();
        ~Scheduler();
        virtual void algorithm();
        virtual void tick();
        bool done() {return is_done;};
        int time() {return current_time;};
        vector<Process*> processes;
    protected:
        Process* current_process;
        list<Process*> waiting;
        bool is_done;
        int current_time;
};

class RRScheduler : public Scheduler {
    public:
        virtual void algorithm();
        RRScheduler(vector<Process*> new_p);
    protected:
        int turn;
};