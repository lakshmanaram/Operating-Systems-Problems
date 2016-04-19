// detecting cycles in a graph using dfs at each node - single instances of a resource
// therefore resources can be neglected and cycles are only found between processes
#include<bits/stdc++.h>
using namespace std;
vector<bool> vis;
bool deadlock_found = false;
struct gnode{                                                                   //individual node element
    vector<int> children;                                                       //children index values
};
class graph{
public:
    int current_dfs_node;
    // stores the node that initiates the dfs
    vector<gnode> gnodes;
    graph(int k){                                                               //constructor which takes number of nodes as input
        gnodes.resize(k);
    }
    void dfs_recurse(int n){
        for(int i=0;i < gnodes[n].children.size();i++){
            if(vis[gnodes[n].children[i]]==false){
                vis[gnodes[n].children[i]] = true;
                dfs_recurse(gnodes[n].children[i]);
            }else{
                if(gnodes[n].children[i] == current_dfs_node)
                // the node that initiated the dfs is met again
                    deadlock_found = true;
            }
        }
    }
    void dfs(int n){
        current_dfs_node = n;
        vis.resize(gnodes.size());
        fill(vis.begin(),vis.end(),false);
        vis[n] = true;
        dfs_recurse(n);
    }
    void add_node(int c, int k){
        gnodes[c].children.push_back(k);
    }
};
int main(){
    int n,e;
    cout<<"Enter number of processes: ";
    cin>>n;                                                                     //number of nodes
    cout<<"Enter the number of edges: ";
    cin>>e;                                                                     //number of edges
    graph g(n);
    cout<<"Enter edges (u v format - directed edge from u to v - 0 indexed processes)\n";
    for(int i=0;i<e;i++){                                                       //adding all the edges
        int a,b;
        cin>>a>>b;
        g.add_node(a,b);
    }
    for(int i=0;i<n && !deadlock_found;i++){
    // dfs is initiated from each node
        g.dfs(i);
    }
    if(deadlock_found)
        cout<<"Deadlock detected, cycle exists in the graph";
    else
        cout<<"No deadlocks found";
    // g.display_values();
    return 0;
}
