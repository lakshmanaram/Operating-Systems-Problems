#include <bits/stdc++.h>
using namespace std;
struct process{
	int bt, at, tt, prio, id,burst;
};
bool func(process a, process b){		//function used to sort by priority
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
		cin>>ps[i].bt>>ps[i].at>>ps[i].prio;	//burst time, arrival time, priority
		ps[i].id = i+1;
		ps[i].burst = ps[i].bt;					// bt is temperory burst time that changes in the loop & burst is the fixed burst for future reference
		totalburst += ps[i].bt;
	}
	sort(ps.begin(),ps.end(),func);		// sorting the processes by priority
	vector<int> ans;
	int size = 0;
	for(int i = 0;i<totalburst;){
		// finding the process for every unit of time until the overall burst time gets over
		int j;
		for(j = 0;j < ps.size();j++){
			if(ps[j].at<=i&&ps[j].bt!=0)
				break;
				// finding the right process
		}
		if(j!=ps.size()){
			while(ps[j].bt!=0){
				ans.push_back(ps[j].id);
				i++;
				ps[j].bt--;
			}
			ps[j].tt = i - ps[j].at;	// total time taken since the arrival - turnaround time
		}
		else{
			ans.push_back(0);
			i++;
		}
	}
/*
	// outputs the actual grantt chart for every time unit
	for(int i = 0; i< ans.size();i++)
		cout<<ans[i]<<" ";
	cout<<endl;
*/

	//formatted grantt chart
	cout<<"0 -> ";
	for(int i=1;i<ans.size();i++){
		while(ans[i]==ans[i-1])
			i++;
		cout<<"P"<<ans[i-1]<<" -> "<<i<<" -> ";
	}
	cout<<"ends"<<endl;

	// waiting time, burst time and turnaround time table
	int avgwait = 0, avgtt = 0;
	cout<<" id   waiting time   burst time  turnaround time"<<endl;;
	for(int i=0;i<ps.size();i++){
		cout<<ps[i].id<<"        "<<ps[i].tt - ps[i].burst<<"              "<<ps[i].burst<<"               "<<ps[i].tt<<endl;
		avgtt += ps[i].tt;
		avgwait += ps[i].tt - ps[i].burst;
	}
	cout<<"avg waiting time "<<avgwait/n<<endl;
	cout<<"avg turnaround time "<<avgtt/n<<endl;
	return 0;
}
