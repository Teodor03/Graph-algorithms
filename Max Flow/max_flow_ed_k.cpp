#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int Max_N=1000000;
const int Infinity=999999999;

struct Edge{
int to;
int weight;
Edge * opposite;
};

int n,m,source,sink;
vector<Edge> graph [Max_N];

int min_to_there[Max_N];
int parent [Max_N];
int num_son [Max_N];

bool visited [Max_N];

bool BFS(){

fill(min_to_there,min_to_there+n,Infinity);
fill(visited,visited+n,false);

queue<int> queuem;
visited[source]=true;
queuem.push(source);
parent [source]=-1;
int current;

while(!queuem.empty()){
    current=queuem.front();
    queuem.pop();
        for(int i=0;i<graph[current].size();i++){
            if(!visited[graph[current][i].to] && graph[current][i].weight!=0){

                visited[graph[current][i].to]=true;
                parent[graph[current][i].to]=current;
                num_son[graph[current][i].to]=i;
                min_to_there[graph[current][i].to]=min(min_to_there[current],graph[current][i].weight);
                queuem.push(graph[current][i].to);

            }
        }
}

return visited [sink];
}

int max_flow(){
int result=0;
int curr,min_found;
while(BFS()){
    min_found=min_to_there[sink];
    curr=sink;
    while(parent[curr]!=-1){
        graph[parent[curr]][num_son[curr]].weight-=min_found;
        (* graph[parent[curr]][num_son[curr]].opposite).weight+=min_found;
        curr=parent[curr];
    }
    result+=min_found;
}
return result;
}

void input(){
cin>>n>>m>>source>>sink;
source--;
sink--;
int a,b,c;
Edge first,second;
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
    graph[a][graph[a].size()-1].opposite=&graph[b][graph[b].size()-1];
    graph[b][graph[b].size()-1].opposite=&graph[a][graph[a].size()-1];
}
return;
}
void output(){
cout<<max_flow();
}
int main(){
ios_base::sync_with_stdio(false);
input();
output();
return 0;
}
