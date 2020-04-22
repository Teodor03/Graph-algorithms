#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;

const int Max_N=1000000;

struct edge{
int from;
int to;
int weight;
bool operator <(edge o)const{
return weight>o.weight;
}
};

int n,m,num_comp;
vector< pair<int,int> > graph[Max_N];

//heap to get min edges
priority_queue<edge> q;

int parent[Max_N];
int depth [Max_N];

void init_dsu(){
for(int i=0;i<n;i++){
    parent[i]=i;
    depth[i]=1;
}
return;
}

int dsu_search(int curr){
if(parent[curr]==curr){
    return curr;
}
return parent[curr]=dsu_search(parent[curr]);
}

void kruskal(){
init_dsu();
edge curr_edge;
int p1,p2;
while(num_comp!=1){
    curr_edge=q.top();
    q.pop();
    p1=dsu_search(curr_edge.from);
    p2=dsu_search(curr_edge.to);
    if(p1!=p2){
        if(depth[p1]>depth[p2]){
            parent[p2]=p1;
        }else{
            if(depth[p1]<depth[p2]){
                parent[p1]=p2;
            }else{
                parent[p2]=p1;
                depth[p1]++;
            }
        }
        cout<<"Edge: "<<curr_edge.from<<" "<<curr_edge.to<<" "<<curr_edge.weight<<endl;
        num_comp--;
    }
}
return;
}

void input_graph(){
ios_base::sync_with_stdio(false);
cin>>n>>m;
num_comp=n;
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    //two-directional roads standart
    graph[a].push_back({b,c});
    graph[b].push_back({a,c});
    q.push({a,b,c});
}
return;
}

int main(){
input_graph();
kruskal();
return 0;
}
