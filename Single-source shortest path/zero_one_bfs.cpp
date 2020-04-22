#include<iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;

const int Max_N=1000000;
const int Inf=999999999;

//true for weight one false for weight zero
vector< pair<int,bool> > graph [Max_N];

int n,m,start;

int d[Max_N];
deque<int> q;

void zero_one_bfs(){
fill(d,d+n,Inf);
d[start]=0;
q.clear();
q.push_back(start);
int curr;
while(!q.empty()){
    curr=q.front();
    q.pop_front();
    for(int i=0;i<graph[curr].size();i++){
        if(graph[curr][i].second){
            if((d[curr]+1)<d[graph[curr][i].first]){
                d[graph[curr][i].first]=d[curr]+1;
                q.push_back(graph[curr][i].first);
            }
        }else{
            if(d[curr]<d[graph[curr][i].first]){
                d[graph[curr][i].first]=d[curr];
                q.push_front(graph[curr][i].first);
            }
        }
    }
}
return;
}

/*

Example 1:

5 5 1
1 5 0
5 4 0
4 3 0
3 2 0
1 2 1

Example 2:

7 8 1
1 2 1
1 4 1
2 3 1
4 3 0
4 5 0
5 6 1
6 3 1
3 7 0

*/

int main(){
cin>>n>>m>>start;
start--;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    if(c==0){
        graph[a].push_back({b,false});
    }else{
        graph[a].push_back({b,true});
    }
}
zero_one_bfs();
for(int i=0;i<n;i++){
    cout<<d[i]<<endl;
}
return 0;
}
