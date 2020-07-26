#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int Max_N=100000;
const int Inf=999999999;


struct edge{

    int to;
    int cap;
    int price;

    edge * opp;

};

int n,m,k,source,sink;

vector<edge> graph [Max_N];

void push_new_edge(int a, int b, int c, int d){

    static edge new_edge;
    new_edge.to=b;
    new_edge.cap=c;
    new_edge.price=d;
    graph[a].push_back(new_edge);
    new_edge.to=a;
    new_edge.cap=0;
    new_edge.price=(-1)*d;
    graph[b].push_back(new_edge);
    graph[a].at(graph[a].size()-1).opp=&graph[b].at(graph[b].size()-1);
    graph[b].at(graph[b].size()-1).opp=&graph[a].at(graph[a].size()-1);

return;
}

int min_dist [Max_N];
int parent [Max_N];
int num_son[Max_N];

bool inque [Max_N];
int num_vis [Max_N];
queue<int> queuem;

void SPFA(){ //finding shortest paths with negative weights with shortest path faster algorithm (best for this case)

fill(num_vis,num_vis+n,0);
fill(min_dist,min_dist+n,Inf);
fill(parent,parent+n,-1);
fill(num_son,num_son+1,-1);

queuem.push(source);
inque[source]=true;
num_vis[source]=1;
min_dist[source]=0;

while(!queuem.empty()){
    int curr=queuem.front();
    queuem.pop();
    inque[curr]=false;
    for(int i=0;i<graph[curr].size();i++){
        if(graph[curr][i].cap>0){
            edge curr_edge=graph[curr][i];
            if((min_dist[curr]+curr_edge.price)<min_dist[curr_edge.to]/* and inque![curr_edge.to]*/){
                min_dist[curr_edge.to]=min_dist[curr]+curr_edge.price;
                parent[curr_edge.to]=curr;
                num_son[curr_edge.to]=i;
                if(!inque[curr_edge.to]){
                    queuem.push(curr_edge.to);
                    num_vis[curr_edge.to]++;
                    inque[curr_edge.to]=true;
                    if(num_vis[curr_edge.to]>=n){
                        return;
                    }
                }
            }
        }
    }

}

return;
}

int find_min_cost_flow(){

    int curr_flow=0;
    int curr_price=0;
    bool have_reached_limit=false;
    while(true){
        SPFA();
        if(num_vis[sink]==0){
            cout<<"Flow K not possible! Maximum possible flow is: "<<curr_flow<<" .";
            goto end_while;
        }

        int curr=sink;
        int min_flow=Inf;
        while(curr!=source){
            min_flow=min(min_flow,graph[parent[curr]][num_son[curr]].cap);
            curr=parent[curr];
        }
        //cout<<"Curr min flow: "<<min_flow<<endl;
        if(min_flow>=(k-curr_flow)){
            have_reached_limit=true;
            min_flow=(k-curr_flow);
        }

        curr_flow+=min_flow;
        curr=sink;
        while(curr!=source){
            graph[parent[curr]][num_son[curr]].cap-=min_flow;
            graph[parent[curr]][num_son[curr]].opp->cap+=min_flow;
            curr_price+=graph[parent[curr]][num_son[curr]].price*min_flow;
            curr=parent[curr];

        }

        if(have_reached_limit){
            goto end_while;
        }
    }

    end_while:;

    return curr_price;
}

/*
    4 5 20 1 4
    1 2 25 10
    1 3 30 50
    2 3 20 8
    2 4 40 30
    3 4 25 12
*/

int main(){
ios_base::sync_with_stdio(false);
cin>>n>>m>>k>>source>>sink;
source--;
sink--;
int a,b,c,d;// from, to, capacity, price
for(int i=0;i<m;i++){
    cin>>a>>b>>c>>d;
    a--;
    b--;
    push_new_edge(a,b,c,d);
}
cout<<"Minimum cost:"<<find_min_cost_flow();
return 0;
}
