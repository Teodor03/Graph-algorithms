#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

const int Max_N=1000000;
const int Max_log_N=30;
const int inf=999999999;

int n,root,num_o=0;


vector<int> graph [Max_N];

vector<int> oiler_path;
vector<int> heights;
int first_occur [Max_N];
bool visited [Max_N];

void first_dfs(int curr,int h){
visited[curr]=true;
heights.push_back(h);
oiler_path.push_back(curr);
first_occur[curr]=min(first_occur[curr],num_o);
num_o++;
    for(int i=0;i<graph[curr].size();i++){
        if(!visited[graph[curr][i]]){
            first_dfs(graph[curr][i],h+1);
            num_o++;
            heights.push_back(h);
            oiler_path.push_back(curr);
        }
    }
return;
}

int s_l;
pair<int,int> sparse_table [Max_N][Max_log_N];
vector<int> max_log;

void calc_max_log(){
max_log.resize(s_l+1);
int curr_s=0,curr_s_t=1;
for(int i=0;i<=s_l;i++){
    if(2*curr_s_t<=i){
        curr_s++;
        curr_s_t*=2;
    }
    max_log[i]=curr_s;
}
return;
}

void build_sparse_table(){
s_l=heights.size();
calc_max_log();
for(int i=0;i<s_l;i++){
    sparse_table[i][0].first=heights[i];
    sparse_table[i][0].second=i;
}

for(int i=1;i<max_log[s_l];i++){
    for(int j=0;j<s_l;j++){
        if((j+(1<<(i-1)))<s_l){
            if(sparse_table[j][i-1].first<sparse_table[j+(1<<(i-1))][i-1].first){
                sparse_table[j][i].first=sparse_table[j][i-1].first;
                sparse_table[j][i].second=sparse_table[j][i-1].second;
            }else{
                sparse_table[j][i].first=sparse_table[j+(1<<(i-1))][i-1].first;
                sparse_table[j][i].second=sparse_table[j+(1<<(i-1))][i-1].second;
            }
        }else{
            sparse_table[j][i].first=inf;
            sparse_table[j][i].second=0;
        }
    }
}
return;
}

pair<int,int> find_min_sparse_table(int l,int r){
if(l<0 or l>=s_l or r<0 or r>=s_l){
    return {inf,0};
}
if(r<l){
    swap(l,r);
}
int len=r-l+1;
int sec_j=r+1-(1<<max_log[len]);
//return min(sparse_table[l][max_log[len]].first,sparse_table[sec_j][max_log[len]]);
if(sparse_table[l][max_log[len]].first<sparse_table[sec_j][max_log[len]].first){
    return sparse_table[l][max_log[len]];
}else{
    return sparse_table[sec_j][max_log[len]];
}
}

/*

7 1
1 2
2 5
2 6
1 3
1 4
4 7

*/


int main(){
ios_base::sync_with_stdio(false);
cin>>n>>root;
root--;
int a,b;
for(int i=0;i<n-1;i++){
    cin>>a>>b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
}
fill(first_occur,first_occur+n,inf);
first_dfs(root,0);
build_sparse_table();
int q;
cin>>q;
for(int i=0;i<q;i++){
    cin>>a>>b;
    a--;
    b--;
    cout<<"Result: Height:"<<find_min_sparse_table(first_occur[a],first_occur[b]).first<<" "<<oiler_path.at(find_min_sparse_table(first_occur[a],first_occur[b]).second)+1<<endl;
}
return 0;
}
