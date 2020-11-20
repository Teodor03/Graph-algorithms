#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

//In this hld will be implemented the ability to change specific edge value and find the max edge value in a path.

const int Max_N=1000000;
const int m_Inf=-999999999;

struct segment_tree_node{
    int c_max;
};

struct segment_tree{

const int * or_arr;
int or_arr_s;

segment_tree_node * m_arr;

void init_segment_tree(int i,int l,int r){
    if(l==r){
        m_arr[i].c_max=or_arr[l];
        return;
    }
    int m=(l+r)/2;
    init_segment_tree(2*i+1,l,m);
    init_segment_tree(2*i+2,m+1,r);
    m_arr[i].c_max=max(m_arr[2*i+1].c_max,m_arr[2*i+2].c_max);
    return;
}

segment_tree (const int * or_ar,int or_ar_s){
    or_arr=or_ar;
    or_arr_s=or_ar_s;
    m_arr=new segment_tree_node[or_arr_s*4+1];
    init_segment_tree(0,0,or_arr_s-1);
}

int find_in_int (int i,int l,int r,int s_l,int s_r){
    if(s_r<s_l){
        swap(s_l,s_r);
    }
    if(l==s_l and r==s_r){
        return m_arr[i].c_max;
    }
    int m=(l+r)/2;
    if(s_r<(m+1)){
        return find_in_int(2*i+1,l,m,s_l,s_r);
    }
    if(m<s_l){
        return find_in_int(2*i+2,m+1,r,s_l,s_r);
    }
    return max( find_in_int(2*i+1,l,m,s_l,m) , find_in_int(2*i+2,m+1,r,m+1,s_r) );
}

void update_spec_val(int i,int l,int r,int upd_i,int upd_v){
    if(l==r){
        m_arr[i].c_max=upd_v;
        return;
    }
    int m=(l+r)/2;
    if(upd_i<(m+1)){
        update_spec_val(2*i+1,l,m,upd_i,upd_v);
    }else{
        update_spec_val(2*i+2,m+1,r,upd_i,upd_v);
    }
    m_arr[i].c_max=max(m_arr[2*i+1].c_max,m_arr[2*i+2].c_max);
    return;
}

};


int n;
vector< pair<int,int> > graph [Max_N];

int par[Max_N],par_i[Max_N],depth [Max_N],heav_ed[Max_N];

int init_dfs(int curr,int p){
    par[curr]=p;
    int curr_s=1,max_f=0,curr_f;
    for(int i=0;i<graph[curr].size();i++){
        if(graph[curr][i].first!=p){
            par_i[graph[curr][i].first]=i;
            depth[graph[curr][i].first]=depth[curr]+1;
            curr_f=init_dfs(graph[curr][i].first,curr);
            if(curr_f>max_f){
                max_f=curr_f;
                heav_ed[curr]=i;
            }
            curr_s+=curr_f;
        }
    }
    if(max_f==0){
        heav_ed[curr]=-1;
    }
    return curr_s;
}

bool vis [Max_N];

int head_p [Max_N];

int pos [Max_N];
vector<int> st_dec;


void constr_hld_rec(int curr,int f_curr_head){
    vis[curr]=true;
    head_p[curr]=f_curr_head;
    if(heav_ed[curr]!=-1){
        st_dec.push_back(graph[curr][heav_ed[curr]].second);
        pos[graph[curr][heav_ed[curr]].first]=st_dec.size()-1;
        //head_p[graph[curr][heav_ed[curr]].first]=f_curr_head;
        constr_hld_rec(graph[curr][heav_ed[curr]].first,f_curr_head);
    }
    for(int i=0;i<graph[curr].size();i++){
        if(!vis[graph[curr][i].first]){
            constr_hld_rec(graph[curr][i].first,graph[curr][i].first);
        }
    }
    return;
}

segment_tree * seg_tr_hld;

void init_hld(){
    init_dfs(0,-1);
    par_i[0]=-1;
//    cout<<"Parent"<<endl;
//    for(int i=1;i<n;i++){
//        cout<<i<<" : "<<graph[par[i]][par_i[i]].second<<endl;
//    }
//    cout<<"Depth"<<endl;
//    for(int i=0;i<n;i++){
//        cout<<i+1<<" : "<<depth[i]<<endl;
//    }
//    cout<<"Heavy edge"<<endl;
//    for(int i=0;i<n;i++){
//        cout<<i+1<<" : "<<heav_ed[i]<<endl;
//    }
    constr_hld_rec(0,0);
//    cout<<"Path"<<endl;
//    for(int i=0;i<st_dec.size();i++){
//        cout<<st_dec[i]<<endl;
//    }
//    cout<<"Location"<<endl;
//    for(int i=0;i<n;i++){
//        cout<<i+1<<" : "<<pos[i]<<endl;
//    }
//    cout<<"Heads"<<endl;
//    for(int i=0;i<n;i++){
//        cout<<i+1<<" : "<<head_p[i]+1<<endl;
//    }
//    cout<<endl;
    seg_tr_hld = new segment_tree(&st_dec[0],st_dec.size());
//    seg_tr_hld->update_spec_val(0,0,seg_tr_hld->or_arr_s-1,6,16);
//    cout<<seg_tr_hld->find_in_int(0,0,seg_tr_hld->or_arr_s-1,4,7);

    return;
}

int querry_max(int a_i,int b_i){
    a_i--;
    b_i--;
    int res=m_Inf;
    while(head_p[a_i]!=head_p[b_i]){
        if(depth[head_p[a_i]]<depth[head_p[b_i]]){
            swap(a_i,b_i);
        }
            //cout<<"Info searching : "<<a_i<<" "<<b_i<<" "<<res<<endl;
            //climb a
            if(head_p[a_i]==a_i){
                res=max( res,graph[par[a_i]][par_i[a_i]].second );
                a_i=par[a_i];
            }else{
                res=max( res,seg_tr_hld->find_in_int(0,0,seg_tr_hld->or_arr_s-1, pos[a_i] , pos[ graph[head_p[a_i]][heav_ed[head_p[a_i]]].first ] ) );
                a_i=head_p[a_i];
            }
    }
    if(a_i==b_i){
        return res;
    }
    if(depth[b_i]>depth[a_i]){
        swap(a_i,b_i);
    }
    res=max( res,seg_tr_hld->find_in_int(0,0,seg_tr_hld->or_arr_s-1,  pos[a_i] , pos[ graph[b_i][heav_ed[b_i]].first ]  ) );
    return res;
}

void querry_update(int ind,int new_val){//change the weight of the edge {par[ind] and ind} and rev
    ind--;
    if(ind==0){
        return;
    }
    if(head_p[ind]==ind){
        graph[par[ind]][par_i[ind]].second=new_val;
        graph[ind][0].second=new_val;
    }else{
        seg_tr_hld->update_spec_val(0,0,seg_tr_hld->or_arr_s-1, pos[ind],new_val );
    }
    return;
}

/*
16
1 2 1
2 4 2
4 8 3
4 9 4
2 5 5
2 6 6
1 3 7
3 7 8
7 10 9
7 11 10
10 12 11
10 13 12
13 15 13
13 16 14
11 14 15
*/

int main (){
cin>>n;
int a,b,c;
for(int i=0;i<n-1;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    graph[a].push_back({b,c});
    graph[b].push_back({a,c});
}
init_hld();
querry_update(7,1);
cout<<querry_max(8,10);



return 0;
}
