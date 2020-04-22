#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

const int Max_N=1000000;
const int Inf=999999999;

int n,m,start;

struct r{
int c;
int i;
bool operator <(r other)const{
    return c>other.c;
}
};

vector< pair<int,int> > graph [Max_N];
int d [Max_N];
priority_queue<r> q;

void Dijkstra(){
fill(d,d+n,Inf);
d[start]=0;
q.push({0,start});
r curr;
while(!q.empty()){
    curr=q.top();
    q.pop();
    for(int j=0;j<graph[curr.i].size();j++){
        if((curr.c+graph[curr.i][j].second)<d[graph[curr.i][j].first]){
            d[graph[curr.i][j].first]=(curr.c+graph[curr.i][j].second);
            q.push({d[graph[curr.i][j].first],graph[curr.i][j].first});
        }
    }
}
return;
}

/*

4 6 1
1 2 1
1 3 1000
1 4 1000
2 3 2
2 4 5
3 4 1

*/

int main(){
cin>>n>>m>>start;
start--;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    graph[a].push_back({b,c});
}
Dijkstra();
for(int i=0;i<n;i++){
    cout<<i<<" : "<<d[i]<<endl;
}
return 0;
}
