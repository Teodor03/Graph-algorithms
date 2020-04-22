#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int Max_N=1000000;

int n,m,time;

vector<int> graph [Max_N];
bool visited [Max_N];
int tim [Max_N];
int low [Max_N];

void dfs(int curr,int p=-1){
time++;
visited[curr]=true;
tim[curr]=time;
low[curr]=time;
    for(int i=0;i<graph[curr].size();i++){
        if(graph[curr][i]!=p){
        if(visited[graph[curr][i]]){
            low[curr]=min(low[curr],tim[graph[curr][i]]);
        }else{
            dfs(graph[curr][i],curr);
            low[curr]=min(low[curr],low[graph[curr][i]]);
            if(low[graph[curr][i]]>tim[curr]){
                cout<<"Found bridge: "<<curr+1<<" "<<graph[curr][i]+1<<endl;
            }
        }
        }
    }
return;
}

void find_bridges(){
time=0;
fill(visited,visited+n,false);
fill(tim,tim+n,-1);
fill(low,low+n,-1);
for(int i=0;i<n;i++){
    if(!visited[i]){
        dfs(i);
    }
}
return;
}

/*

8 9
1 2
1 3
3 2
3 4
2 5
4 5
5 6
6 7
6 8

*/

int main(){
cin>>n>>m;
int a,b;
for(int i=0;i<m;i++){
    cin>>a>>b;
    a--;
    b--;
    graph[a].push_back(b);
}
find_bridges();
for(int i=0;i<n;i++){
    cout<<tim[i]<<" "<<low[i]<<endl;
}
return 0;
}
