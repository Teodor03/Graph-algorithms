#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int Max_N=1000000;
const int Inf = 999999999;

int n,m,so,si;
struct edge{
int to,we,opp;
};

vector<edge> gr [Max_N];

void add_edge(int a,int b,int c){
    edge fo,bac;
    fo.to=b;
    fo.we=c;
    bac.to=a;
    bac.we=0;
    gr[a].push_back(fo);
    gr[b].push_back(bac);
    gr[a][gr[a].size()-1].opp=gr[b].size()-1;
    gr[b][gr[b].size()-1].opp=gr[a].size()-1;
    return;
}

bool vis [Max_N];
int lev [Max_N];
int par [Max_N];
int num_son [Max_N];

void reset_level(){
    for(int i=0;i<n;i++){
        lev[i]=-1;
    }
}

void reset_vis(){
    for(int i=0;i<n;i++){
        vis[i]=false;
    }
}

bool bfs(){
    queue<int> q;
    reset_level();
    lev[so]=0;
    q.push(so);
    int curr;
    while(!q.empty()){
        curr=q.front();
        q.pop();
        for(int i=0;i<gr[curr].size();i++){
            if(lev[gr[curr][i].to]==-1 and gr[curr][i].we!=0){
                lev[gr[curr][i].to]=lev[curr]+1;
                q.push(gr[curr][i].to);
            }
        }
    }
//    for(int i=0;i<n;i++){
//        cout<<i+1<<" : "<<lev[i]<<endl;
//    }
    return lev[si]!=-1;
}

void dfs(int curr){
    for(int i=0;i<gr[curr].size();i++){
        if( (!vis[gr[curr][i].to]) and gr[curr][i].we>0 and (lev[gr[curr][i].to] == lev[curr]+1 ) ){
            vis[gr[curr][i].to]=true;
            par[gr[curr][i].to]=curr;
            num_son[gr[curr][i].to]=i;
            dfs(gr[curr][i].to);
        }
    }
}

bool dfs_driver(){
    reset_vis();
    vis[so]=true;
    par[so]=-1;
    dfs(so);
    return vis[si];
}

int Dinic(){
    int res=0,c,_min;
    while(bfs()){

        while(dfs_driver()){
            _min=Inf;
            c=si;
            while(par[c]!=-1){
                _min=min(_min,gr[par[c]][num_son[c]].we);
                c=par[c];
            }
            c=si;
            while(par[c]!=-1){
                gr[par[c]][num_son[c]].we-=_min;
                gr[c][gr[par[c]][num_son[c]].opp].we+=_min;
                c=par[c];
            }
            res+=_min;
        }

    }

    return res;
}

void input(){
    ios_base::sync_with_stdio(false);
    cin>>n>>m>>so>>si;
    so--;
    si--;
    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        a--;
        b--;
        add_edge(a,b,c);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    input();
    cout<<"Result : "<<Dinic()<<endl;
    return 0;
}
