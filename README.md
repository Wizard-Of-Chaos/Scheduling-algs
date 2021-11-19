# CMSC442SchedulerF21
 A scheduling simulator for CMSC 442.
 Compile with "g++ -g -o Scheduler main.cpp processrunner.cpp processrunner.h".

 Accepts the following arguments when run from the command line:

 Random:

 -r numprocesses

 Adds numprocesses randomly-generated processes to the list of processes to execute.

 FCFS:

 -fcfs optionalfile

 Uses the FCFS algorithm. Takes in an optional argument that specifies a file to read processes from.

 Round Robin:

 -rr optionalfile

 Uses the Round Robin algorithm. Takes in optional file.

 HRRN:

 -hhrn optionalfile

 Uses the HRRN algorithm. Takes in optional file.

 SJF:

 -sjf optionalfile

 Uses the SJF algorithm. Takes in optional file.

 SJR:

 -sjr optionalfile

 Uses the SJR algorithm. Takes in optional file.

 Example run:
 ./Scheduler -r 40 -hrrn file.txt

 Process files are read in as a line with their name, their start time, and their duration, in that order.
 Example:

 MyProcess 5 20

 Written by Alexander Wiecking and Shyheim Williams.

 ALEXANDER WIECKING:
 Wrote out initial scheduler implementation as well as the Round Robin algorithm / FCFS and the stats. Also random processes and test cases.

 SHYHEIM WILLIAMS:
 Wrote out file input, command line args, HRRN, SJR, and SJF algorithm and test cases.
