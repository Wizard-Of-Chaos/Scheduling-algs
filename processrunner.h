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
    int waittime = 0;
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
        int completed = 0;
        int exectime = 0;
        vector<Process*> processes;
    protected:
        int turn;
        Process* current_process;
        list<Process*> waiting;
        bool is_done;
        int current_time;
};

class RRScheduler : public Scheduler {
    public:
        virtual void algorithm();
        RRScheduler(vector<Process*> new_p);
};

class HRRNScheduler : public Scheduler {
	public:
		virtual void algorithm();
		HRRNScheduler(vector<Process*> new_p);
		void HRRNSort(list<Process*> waiting);
		protected:
};

class SJFScheduler : public Scheduler {
	public: 
		virtual void algorithm();
		SJFScheduler(vector<Process*> new_p);
};

class SJRScheduler : public Scheduler {
	public: 
		virtual void algorithm();
		SJRScheduler(vector<Process*> new_p);
};
