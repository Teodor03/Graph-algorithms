#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct edge{
int from;
int to;
int weight;
};

const int Max_N=1000000;
const int Inf=999999999;

int n,m,start;

int d[Max_N];
bool is_neg_circle;

int p[Max_N];

vector<edge> edges_list;

void bellman_ford(){
fill(d,d+n,Inf);
d[start]=0;
p[start]=-1;
int last;
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        last=-1;
        if(d[edges_list[j].from]<Inf){
            if(d[edges_list[j].to]>d[edges_list[j].from]+edges_list[j].weight){
                d[edges_list[j].to]=d[edges_list[j].from]+edges_list[j].weight;
                p[edges_list[j].to]=edges_list[j].from;
                last=edges_list[j].to;
            }
        }
    }
    if(last==-1){
        return;

    }
}
if(last!=-1){
is_neg_circle=true;
cout<<"Negative loop found!"<<endl;
}
return;
}

/*
5 5 1
1 2 5
2 4 -1
4 3 -6
3 2 -4
4 5 2
*/

int main(){
cin>>n>>m>>start;
start--;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    edges_list.push_back({a,b,c});
}
bellman_ford();
if(!is_neg_circle){
    for(int i=0;i<n;i++){
    cout<<d[i]<<endl;
    }
}
return 0;
}
