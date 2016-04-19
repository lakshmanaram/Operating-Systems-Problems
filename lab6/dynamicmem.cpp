// dynamic memory allocation
// Approach time of Processes should be in the ascending order while giving input, otherwise sorting code should be added.
#include <bits/stdc++.h>
using namespace std;

#define MAX 100000
#define MIN 0

int cur_time;
int processes_remaining;
class Process{
public:
    int size, allocated, approach_time, burst_time, start_time;
};
class Partition{
public:
    int size,allocated,end_time;
    // end_time is the time till which the patition is allocated
};

void display(vector <Process> processes)
{
	for (int i = 0; i < processes.size(); ++i)
	{
		if (processes[i].allocated != -1){
			cout << "P" << i << " allocated block " << processes[i].allocated;
            cout << " Approach time " << processes[i].approach_time << " burst_time " << processes[i].burst_time;
            cout << " Start time " << processes[i].start_time << endl;
        }
		else cout << "P" << i << " can't be allocated!" << endl;
	}
}

void FirstFit(vector <Partition> &partitions, vector <Process> &processes)
{
	for (int i = 0; i < processes.size(); i++)
	{
        if(processes[i].approach_time > cur_time)
            break;
        if(processes[i].allocated != -1)
            continue;
		for (int j = 0; j < partitions.size(); j++)
		{
			if (partitions[j].size >= processes[i].size && partitions[j].allocated == -1)
			{
				partitions[j].allocated = i;
				processes[i].allocated = j;
                processes[i].start_time = cur_time;
                partitions[j].end_time = cur_time + processes[i].burst_time;
                processes_remaining--;
				break;
			}
		}
	}
}

void BestFit(vector <Partition> &partitions, vector <Process> &processes)
{
	for (int i = 0, best, bestIndex; i < processes.size(); i++)
	{
        if(processes[i].approach_time > cur_time)
            break;
        if(processes[i].allocated != -1)
            continue;
		best = MAX;
		bestIndex = -1;
		for (int j = 0; j < partitions.size(); j++)
		{
			if (partitions[j].size >= processes[i].size && partitions[j].allocated == -1 && partitions[j].size < best)
			{
				best = partitions[j].size;
				bestIndex = j;
			}
		}
        if(bestIndex!=-1){
            partitions[bestIndex].allocated = i;
            processes[i].allocated = bestIndex;
            processes[i].start_time = cur_time;
            partitions[bestIndex].end_time = cur_time + processes[i].burst_time;
            processes_remaining--;
        }
	}
}

void WorstFit(vector <Partition> &partitions, vector <Process> &processes)
{
	for (int i = 0, best, bestIndex; i < processes.size(); i++)
	{
        if(processes[i].approach_time > cur_time)
            break;
        if(processes[i].allocated != -1)
            continue;
		best = MIN;
		bestIndex = -1;
		for (int j = 0; j < partitions.size(); j++)
		{
			if (partitions[j].size >= max(processes[i].size,best) && partitions[j].allocated == -1)
			{
				best = partitions[j].size;
				bestIndex = j;
			}
		}
        if(bestIndex!=-1){
    		partitions[bestIndex].allocated = i;
    		processes[i].allocated = bestIndex;
            processes[i].start_time = cur_time;
            partitions[bestIndex].end_time = cur_time + processes[i].burst_time;
            processes_remaining--;
        }
	}
}

void free_completed_processes(vector <Partition> &partitions){
    for(int i=0;i<partitions.size();i++){
        if(partitions[i].allocated!=-1 && partitions[i].end_time <= cur_time)
            partitions[i].allocated = -1;
    }
}

int main()
{
	int n,p;
	cout << "Enter number of mem blocks: ";
	cin >> n;
	cout << "Enter block sizes: ";
	vector <Partition> partitions(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> partitions[i].size;
		partitions[i].allocated = -1;
	}
	cout << "Enter number of processes: ";
	cin >> p;
	cout << "Enter amt of mem requested, approach_time, burst_time of each process: ";
	vector <Process> processes(p);
	for (int i = 0; i < p; ++i)
	{
		cin >> processes[i].size >> processes[i].approach_time >> processes[i].burst_time;
		processes[i].allocated = -1;
	}
	while (true)
	{
		cout << "1. First fit\n2. Best Fit\n3. Worst Fit\n\nEnter Choice: ";
		int choice;
		cin >> choice;
        cur_time = 0;
        processes_remaining = processes.size();
        vector <Process> temp_processes = processes;
        vector <Partition> temp_partitions = partitions;
		switch(choice)
		{
			case 1:
            while(processes_remaining!=0){
                free_completed_processes(temp_partitions);
                FirstFit(temp_partitions,temp_processes);
                cur_time++;
            }
			break;
			case 2:
            while(processes_remaining!=0){
                free_completed_processes(temp_partitions);
                BestFit(temp_partitions,temp_processes);
                cur_time++;
            }
			break;
			case 3:
            while(processes_remaining!=0){
                free_completed_processes(temp_partitions);
                WorstFit(temp_partitions,temp_processes);
                cur_time++;
            }
            break;
		}
        display(temp_processes);
	}
	return 0;
}
