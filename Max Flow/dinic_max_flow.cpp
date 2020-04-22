#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int Max_V=10001;
const int Max_cap=999999999;

struct edge{
int to;
int weight;
edge * opp;
};

int n,m,source,sink;
vector<edge> graph[Max_V];

void build_edge(int f,int s,int w){
edge a;
edge b;
a.to=s;
a.weight=w;
graph[f].push_back(a);
b.to=f;
b.weight=0;
graph[s].push_back(b);
graph[f][graph[f].size()-1].opp=&graph[s][graph[s].size()-1];
graph[s][graph[s].size()-1].opp=&graph[f][graph[f].size()-1];
return;
}

bool visited[Max_V];
int lev [Max_V];

bool BFS(){
queue<int> q;
q.push(source);
fill(visited,visited+n,false);
visited[source]=true;
lev[source]=0;
int curr;
while(!q.empty()){
    curr=q.front();
    q.pop();
    for(int i=0;i<graph[curr].size();i++){
        if(!visited[graph[curr][i].to] and graph[curr][i].weight!=0){
            visited[graph[curr][i].to]=true;
            lev[graph[curr][i].to]=lev[curr]+1;
            q.push(graph[curr][i].to);
        }
    }
}
return visited[sink];
}

int prev [Max_V];
int num_son [Max_V];
int min_to [Max_V];

void DFS(int curr){
for(int i=0;i<graph[curr].size();i++){
    if(!visited[graph[curr][i].to] and graph[curr][i].weight!=0 and (lev[graph[curr][i].to]-lev[curr])==1){
        visited[graph[curr][i].to]=true;
        prev[graph[curr][i].to]=curr;
        num_son[graph[curr][i].to]=i;
        min_to[graph[curr][i].to]=min(min_to[curr],graph[curr][i].weight);
        DFS(graph[curr][i].to);
    }
}
return;
}

bool call_DFS(){
prev[source]=-1;
num_son[source]=-1;
min_to[source]=Max_cap;
fill(visited,visited+n,false);
visited[source]=true;
DFS(source);
return visited[sink];
}

int max_flow_dinic(){
int result=0;
int curr,min_pipe;
while(BFS()){
    while(call_DFS()){
        min_pipe=min_to[sink];
        curr=sink;
        while(prev[curr]!=-1){
            graph[prev[curr]][num_son[curr]].weight-=min_pipe;
            (* graph[prev[curr]][num_son[curr]].opp).weight+=min_pipe;
            curr=prev[curr];
        }
        result+=min_pipe;
    }
}
return result;
}

/*
Example:

6 8 1 6
1 2 11
1 3 12
3 2 1
2 4 12
3 5 11
5 4 7
5 6 4
4 6 19

*/

int main(){
ios_base::sync_with_stdio(false);
cin>>n>>m>>source>>sink;
source--;
sink--;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    build_edge(a,b,c);
}
cout<<max_flow_dinic();
return 0;
}
