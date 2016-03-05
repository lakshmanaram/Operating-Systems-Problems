#include <bits/stdc++.h>
using namespace std;
struct process{
	int bt, at, tt, prio, id,burst;
};
bool func(process a, process b){			//function to sort by priority
	if(a.prio == b.prio){
		return (a.at <= b.at)?true:false;
	}
	return (a.prio < b.prio)?true:false;
}
int main(){
	int n;
	int totalburst = 0;
	cout<<" Enter number of processes: ";
	cin>>n;
	cout<<"Enter burst time, arrival time & priority for each process"<<endl;
	vector<process> ps(n);
	for(int i=0;i<ps.size();i++){
		cin>>ps[i].bt>>ps[i].at>>ps[i].prio;
		ps[i].id = i+1;
		ps[i].burst = ps[i].bt;
		totalburst += ps[i].bt;
	}
	//process p = {0,0,0,0};
	//ps.push_back(p);
	sort(ps.begin(),ps.end(),func);
/*	for(int i = 0; i< ps.size();i++)
		cout<<ps[i].prio<<" ";
	cout<<endl;
	prints sorted processes
*/
	vector<int> ans;
	int size = 0;
	for(int i=0;i<ps.size();i++){
		// for every process in the order of priority
		for(int j = ps[i].at;ps[i].bt>0;j++){
			// alotting the time slice to the function.
			while(size <= j){
				// increasing the size of the ans array as we require
				ans.push_back(0);
				size++;
			}
			if(ans[j]==0){
				// alotting the time slice to the specified process
				ans[j] = ps[i].id;
				ps[i].bt -- ;
			}
			if(ps[i].bt==0)
				// to find the turnaround time of the Process
				ps[i].tt = j - ps[i].at + 1;
		}
	}
/*
	prints ans array without formatting (Grantt chart)
	for(int i = 0; i< ans.size();i++)
		cout<<ans[i]<<" ";
	cout<<endl;
*/

	//formatted Grantt chart
	cout<<"0 -> ";
	for(int i=1;i<ans.size();i++){
		while(ans[i]==ans[i-1])
			i++;
		if(ans[i-1]!=0)
			cout<<"P"<<ans[i-1]<<" -> "<<i<<" -> ";
		else
			cout<<" -> "<<i<<" -> ";
	}
	cout<<"ends"<<endl;
	
	int avgwait = 0, avgtt = 0;
	cout<<" id   waiting time   burst time  turnaround time"<<endl;;
	for(int i=0;i<ps.size();i++){
		cout<<setw(2)<<ps[i].id<<"       "<<setw(3)<<ps[i].tt - ps[i].burst<<"           "<<setw(3)<<ps[i].burst<<"           "<<setw(3)<<ps[i].tt<<endl;
		avgtt += ps[i].tt;
		avgwait += ps[i].tt - ps[i].burst;
	}
	cout<<"avg waiting time "<<avgwait/n<<endl;
	cout<<"avg turnaround time "<<avgtt/n<<endl;
	return 0;
}
