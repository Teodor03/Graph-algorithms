#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int Max_N=1000000;

int n,m;

vector<int> graph [Max_N];
vector<int> rev_graph [Max_N];

vector<int> s;
bool visited [Max_N];

void first_dfs(int curr){
    visited[curr]=true;
    for(int i=0;i<graph[curr].size();i++){
        if(!visited[graph[curr][i]]){
        first_dfs(graph[curr][i]);
        }
    }
    s.push_back(curr);
    return;
}

void second_dfs(int curr){
    visited[curr]=true;
    cout<<" "<<curr;
    for(int i=0;i<rev_graph[curr].size();i++){
        if(!visited[rev_graph[curr][i]]){
        second_dfs(rev_graph[curr][i]);
        }
    }
    return;
}

void kosaraju(){
s.clear();
fill(visited,visited+n,false);
for(int i=0;i<n;i++){
    if(!visited[i]){
        first_dfs(i);
    }
}
fill(visited,visited+n,false);
for(int i=n-1;i>-1;i--){
    if(!visited[s[i]]){
        cout<<"Found new SCC: ";
        second_dfs(s[i]);
        cout<<endl;
    }
}
return;
}

/*

5 5
1 2
2 3
3 1
2 4
4 5

*/

int main(){
cin>>n>>m;
int a,b;
for(int i=0;i<m;i++){
    cin>>a>>b;
    a--;
    b--;
    graph[a].push_back(b);
    rev_graph[b].push_back(a);
}
kosaraju();
return 0;
}
