#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;

const int Max_N=1000000;

struct edge{
int to;
int weight;
bool operator <(edge other)const{
    return weight>other.weight;
}
};

vector<edge> graph [Max_N];
int n,m;

bool visited [Max_N];
priority_queue<edge> q;
int result=0;


void prim_mlogn(){
visited[0]=true;
for(int i=0;i<graph[0].size();i++){
    q.push(graph[0][i]);
}
edge curr;
while(!q.empty()){
    curr=q.top();
    q.pop();
    if(!visited[curr.to]){
        result+=curr.weight;
        visited[curr.to]=true;
        for(int i=0;i<graph[curr.to].size();i++){
            if(!visited[graph[curr.to][i].to]){
                q.push(graph[curr.to][i]);
            }
        }
    }
}
return;
}

int main(){
ios_base::sync_with_stdio(false);
cin>>n>>m;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    graph[a].push_back({b,c});
    graph[b].push_back({a,c});
}
prim_mlogn();
cout<<result;
return 0;
}
