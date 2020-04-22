#include<iostream>
#include<vector>
using namespace std;

const int Max_N=100000000;

int n,m;
vector<int> graph [Max_N];

bool visited [Max_N];

void DFS(int curr){
visited[curr]=true;
cout<<" "<<curr;
for(int i=0;i<graph[curr].size();i++){
    if(!visited[graph[curr][i]]){
        DFS(graph[curr][i]);
    }
}
return;
}

void find_connected_comp(){
for(int i=0;i<n;i++){
    if(!visited[i]){
       cout<<endl<<"New connected comp:";
       DFS(i);
    }
}
return;
}

int main(){
cin>>n>>m;
int a,b;
for(int i=0;i<m;i++){
    cin>>a>>b;
    a--;
    b--;
    graph[a].push_back(b);
}
find_connected_comp();
return 0;
}
