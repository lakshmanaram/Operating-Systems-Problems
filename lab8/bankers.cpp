#include <iostream>
#include <vector>
using namespace std;

struct process 
{
    // max how much is needed, how much allocated already, need=max - allocation
    vector <int> max,allocation,need;
    bool completed;
};

bool isLess(vector <int> a,vector<int> b)
{
    for (int i = 0; i < a.size(); ++i)
        if (a[i] > b[i]) return false;
    return true;
}

vector <int> sum(vector <int> a, vector <int> b)
{
    vector <int> res(a.size());
    for (int i = 0; i < a.size(); ++i)
        res[i] = a[i] + b[i];
    return res;
}

vector <int> getAvailableResources(int r)
{
    vector <int> available(r);
    cout << "Enter current no. of available instances of each resource:\n";
    for (int i = 0; i < r; ++i) cin >> available[i];
    return available;
}

void Processes(vector<process> &P,int n,int r)
{
    // Defines need and allocation matrices.
    cout << "Enter the MAX matrix:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i << ": ";
        process p;
        p.max.resize(r);
        p.allocation.resize(r);
        p.need.resize(r);
        p.completed = false;
        for (int j = 0; j < r; ++j)
        {
            cin >> p.max[j];
        }
        P.push_back(p);
    }

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < n; ++i)
    {
       cout << "P" << i << ": ";
       for (int j = 0; j < r; ++j)
       {
           cin >> P[i].allocation[j];
           P[i].need[j] = P[i].max[j] - P[i].allocation[j];
       }
    }
}

// initially work matrix = available matrix
void Bankers(vector <process>& P,vector <int>& work)
{
    bool allCompleted = false;
    vector <int> safeSeq;
    while (allCompleted == false)
    {
        allCompleted = true;    // flag to check if all processes are completed
        bool noneAllocated = true;     // to check if at least 1 process was allocated resource
        for (int i = 0; i < P.size(); ++i)
        {
            if (P[i].completed) continue;
            allCompleted = false;
            if (isLess(P[i].need,work)) // if need < work
            {
                // complete job and release P[i] resources
                work = sum(P[i].allocation,work);
                P[i].completed = true;
                safeSeq.push_back(i);
                noneAllocated = false;
            }
        }
        if (allCompleted == false and noneAllocated == true)
        {
            cout << "Deadlock!" << endl;
            return;
        }
    }
    for (int i = 0; i < safeSeq.size(); ++i) cout << safeSeq[i] << ", ";
}

int main()
{
    int n,r;
    cout << "Number of Processes: " ;
    cin >> n;
    cout << "Enter number of Resources: ";
    cin >> r;
    vector <int> available = getAvailableResources(r);
    vector <process> P;
    Processes(P,n,r);
    Bankers(P,available);
    return 0;
}