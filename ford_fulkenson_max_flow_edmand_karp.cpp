#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int Max_N=100000;

struct edge{
int to;
int weight;
edge * opp;
};

struct backed{
int first;
int second;
};

vector<edge> graph [Max_N];
int n,m,source,sink;

bool visited [Max_N];

//parent,num_child
backed from_where[Max_N];

bool BFS(){
for(int i=0;i<n;i++){
    visited[i]=false;
    from_where[i].first=0;
    from_where[i].second=0;
}
visited [source]=true;
from_where [source].first=-1;
from_where [source].second=-1;
queue<int> queuem;
queuem.push(source);
int current;
while(!queuem.empty()){
    current=queuem.front();
    queuem.pop();
    for(int i=0;i<graph[current].size();i++){
        if(!visited[graph[current][i].to] and graph[current][i].weight>0){
            from_where[graph[current][i].to].first=current;
            from_where[graph[current][i].to].second=i;
            visited[graph[current][i].to]=true;
            queuem.push(graph[current][i].to);
        }
    }
}
return visited[sink];
}

int minimum(int a,int b){
if(a<b){
    return a;
}
return b;
}

int max_flow(){
int result=0;
int min_found;
int curr;
while(BFS()){
    min_found=99999999;
    curr=sink;
    while(from_where[curr].first!=-1){
        min_found=minimum(min_found,graph[from_where[curr].first][from_where[curr].second].weight);
        curr=from_where[curr].first;
    }
    curr=sink;
    while(from_where[curr].first!=-1){
        graph[from_where[curr].first][from_where[curr].second].weight-=min_found;
        (* graph[from_where[curr].first][from_where[curr].second].opp).weight+=min_found;
        curr=from_where[curr].first;
    }
    result+=min_found;
}
return result;
}

int main(){
ios_base::sync_with_stdio(false);
cin>>n>>m>>source>>sink;
source--;
sink--;
int a,b,c;
edge * s;
edge * r;
edge first,second;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    first.to=b;
    first.weight=c;
    graph[a].push_back(first);
    second.to=a;
    second.weight=0;
    graph[b].push_back(second);
    graph[a][graph[a].size()-1].opp=&graph[b][graph[b].size()-1];
    graph[b][graph[b].size()-1].opp=&graph[a][graph[a].size()-1];
}
cout<<max_flow();
return 0;
}
