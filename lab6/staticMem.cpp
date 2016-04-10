#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 100000
#define MIN 0

struct Block
{
	int size,allocated;
};

struct Process
{
	int size,allocated;
};

void display(vector <Process> processes)
{
	for (int i = 0; i < processes.size(); ++i)
	{
		if (processes[i].allocated != -1)
			cout << "P" << i << " allocated block " << processes[i].allocated << endl;
		else cout << "P" << i << " can't be allocated!" << endl;
	}
}

void FirstFit(vector <Block> partitions, vector <Process> processes)
{
	for (int i = 0; i < processes.size(); i++)
	{
		for (int j = 0; j < partitions.size(); j++)
		{
			if (partitions[j].size >= processes[i].size && partitions[j].allocated == -1)
			{
				partitions[j].allocated = i;
				processes[i].allocated = j;
				break;
			}
		}
	}
	display(processes);
}

void BestFit(vector <Block> partitions, vector <Process> processes)
{
	for (int i = 0, best, bestIndex; i < processes.size(); i++)
	{
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
		partitions[bestIndex].allocated = i;
		processes[i].allocated = bestIndex;
	}
	display(processes);
}

void WorstFit(vector <Block> partitions, vector <Process> processes)
{
	for (int i = 0, best, bestIndex; i < processes.size(); i++)
	{
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
		partitions[bestIndex].allocated = i;
		processes[i].allocated = bestIndex;
	}
	display(processes);
}

int main()
{
	int n,p;
	cout << "Enter number of mem blocks: ";
	cin >> n;
	cout << "Enter block sizes: ";
	vector <Block> partitions(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> partitions[i].size;
		partitions[i].allocated = -1;
	}
	cout << "Enter number of processes: ";
	cin >> p;
	cout << "Enter amt of mem requested by each process: ";
	vector <Process> processes(p);
	for (int i = 0; i < p; ++i) 
	{
		cin >> processes[i].size;
		processes[i].allocated = -1;
	}
	while (true)
	{	
		cout << "1. First fit\n2. Best Fit\n3. Worst Fit\n\nEnter Choice: ";
		int choice;
		cin >> choice;
		switch(choice)
		{
			case 1: FirstFit(partitions,processes);
					break;
			case 2: BestFit(partitions,processes);
					break;
			case 3: WorstFit(partitions,processes);
		}
	}
	return 0;
}