#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int Max_N=100000;

int n,m;
vector<int> graph [Max_N];

vector<int> answer;

bool visited [Max_N];

void dfs(int curr){
    visited[curr]=true;

    for(int i=0;i<graph[curr].size();i++){
        if(!visited[graph[curr][i]]){
            dfs(graph[curr][i]);
        }
    }

    answer.push_back(curr);
    return;
}

void top_sort(){
    fill(visited,visited+n,false);
    answer.clear();
    for(int j=0;j<n;j++){
        if(!visited[j]){
            dfs(j);
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
top_sort();
cout<<"Result : ";
for(int i=n-1;i>-1;i--){
    cout<<answer[i]+1<<" ";
}
return 0;
}
