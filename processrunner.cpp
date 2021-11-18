#include "processrunner.h"

using namespace std;

Scheduler::Scheduler()
{
    current_time = 0;
    current_process = nullptr;
    is_done = false;
}

Scheduler::Scheduler(vector<Process*> new_p)
{
    processes = new_p;
    current_time = 0;
    current_process = nullptr;
    is_done = false;
}

Scheduler::~Scheduler()
{
    for(Process* p : processes) {
        delete p;
    }
}

void Scheduler::algorithm() 
//Virtual function; default case is FCFS. Just goes through the list.
//In class extensions, this should be the thing that changes - just sorting the list, really.
{
    if(current_process == nullptr && waiting.size() > 0) {
        current_process = waiting.front();
        waiting.pop_front();
    }

}

void Scheduler::tick() 
{
    //The universe continues on for another microsecond.
    algorithm(); //updates the waitlist
    //Updates all processes history based on their runtime.
    for(Process* p : processes) {
        if (p->complete) { //If the process is done, add a space.
            p->history += ' ';
        }else if (p == current_process) { //If it's the current process, add an X.
            p->history += 'X';
            ++turn;
            ++p->runtime;
            ++exectime;
        }else if (p->ready) { //If it's ready, but not the current process, add a pipe.
            p->history += '|';
            ++p->waittime;
        }else if (p->start == current_time) { //If it's not ready, but it's the time for it to start, throw it in the waitlist and add it to ready.
            if(current_process == nullptr) {
                current_process = p;
                p->ready = true;
                ++p->runtime;
                p->history += 'X';
            } else {
                waiting.push_back(p);
                p->ready = true;
                p->history += 'S';
                ++p->waittime;
            }
        } else { //If it hasn't started and isn't done, add a period.
            p->history += '.';
        }

        if(p->runtime == p->duration && !p->complete) {
            p->complete = true;
            current_process = nullptr;
            turn = 0;
            ++completed;
        }
        //cin.get();
    }
    ++current_time;
    for(Process* p : processes) {
        if(!p->complete) return; //If even a single process isn't done, we're outta here.
    }
    is_done = true;
}

//ROUND ROBIN SCHEDULER
RRScheduler::RRScheduler(vector<Process*> new_p)
{
    processes = new_p;
    current_process = nullptr;
    current_time = 0;
    is_done = false;
    turn = 0;
}

void RRScheduler::algorithm() {
    if(current_process == nullptr && waiting.size() > 0) {
        current_process = waiting.front();
        waiting.pop_front();
    }
    //++turn;
    if(turn == 5) {
        waiting.push_back(current_process);
        current_process = waiting.front();
        waiting.pop_front();
        turn = 0;
    }
}

//HIGHEST RESPONSE RATE NEXT (HRRN) SCHEDULER
HRRNScheduler::HRRNScheduler(vector<Process*> new_p)
{
	processes = new_p;
	current_process = nullptr;
	current_time = 0;
	is_done = false;
	turn = 0;
}

bool HRRNSort(Process* first, Process* second){
	int proc1 = (first->waittime + first->duration) / first->duration;
	int proc2 = (second->waittime + second->duration) / second->duration;
	if(proc1 > proc2){
		return true;
	}else{
		return false;
	}					
}

void HRRNScheduler::algorithm()
{
	//sort list
	waiting.sort(HRRNSort);
	if(current_process == nullptr && waiting.size() > 0){
		current_process = waiting.front();
		waiting.pop_front();	
	}
			
}
//SHORTEST JOB FIRST (SJF) SCHEDULER
SJFScheduler::SJFScheduler(vector<Process*> new_p)
{
	processes = new_p;
	current_process = nullptr;
	current_time = 0;
	is_done = false;
	turn = 0;
}

void SJFScheduler::algorithm(){

}

//SHORTEST JOB REMAINING (SJR) SCHEDULER
SJRScheduler::SJRScheduler(vector<Process*> new_p)
{
	processes = new_p;
	current_process = nullptr;
	current_time =0;
	is_done = false;
	turn = 0;
}

void SJRScheduler::algorithm(){
	
}
