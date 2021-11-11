#include "processrunner.h"

using namespace std;

ProcessRunner::ProcessRunner(vector<Process*> new_p)
{
    processes = new_p;
    current_time = 0;
    current_process = nullptr;
    is_done = false;
}

ProcessRunner::~ProcessRunner()
{
    for(Process* p : processes) {
        delete p;
    }
}

void ProcessRunner::addTime() 
{
    ++current_time; //The universe continues on for another microsecond.
    if(current_process == nullptr) {
        current_process = waiting.front();
        waiting.pop_front();
    }

    //Updates all processes history based on their runtime.
    for(Process* p : processes) {
        if (p->complete) { //If the process is done, add a space.
            p->history += ' ';
        }else if (p == current_process) { //If it's the current process, add an X.
            p->history += 'X';
            ++p->runtime;
        }else if (p->ready) { //If it's ready, but not the current process, add a pipe.
            p->history += '-';
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
            }
        } else { //If it hasn't started and isn't done, add a period.
            p->history += '.';
        }


        if(p->runtime == p->duration && !p->complete) {
            p->complete = true;
            current_process = nullptr;
        }
    }
    for(Process* p : processes) {
        if(!p->complete) return; //If even a single process isn't done, we're outta here.
    }
    is_done = true;
}