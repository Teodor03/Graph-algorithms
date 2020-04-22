#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct edge{
int from;
int to;
int weight;
};

const int Max_N=1000000;
const int Inf=999999999;

int n,m,start;

vector<edge> edge_list;

int d [Max_N];

int _min(int a,int b){
if(a<b){
    return a;
}
return b;
}

void bellman_ford(){
fill(d,d+n,Inf);
d[start]=0;
bool changed;
for(int i=0;i<n-1;i++){
    changed=false;
    for(int j=0;j<m;j++){
        if(d[edge_list[j].from]<Inf){
            if(d[edge_list[j].from]+edge_list[j].weight<d[edge_list[j].to]){
                changed=true;
                d[edge_list[j].to]=d[edge_list[j].from]+edge_list[j].weight;
            }
        }
    }
    if(!changed){
        return;
    }
}
return;
}

/*
Example 1 :
4 6 1
1 2 1
1 3 -1000
1 4 1000
2 4 5
3 4 1
2 3 1

*/

int main(){
cin>>n>>m>>start;
start--;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    edge_list.push_back({a,b,c});
}
bellman_ford();
for(int i=0;i<n;i++){
    cout<<d[i]<<endl;
}
return 0;
}
