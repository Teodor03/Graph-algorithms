#include<iostream>
#include<vector>
using namespace std;

const int Max_N=100000;

int n;
vector<int> tree [Max_N];
int subtr [Max_N];

bool is_centr [Max_N];
vector<int> centroid_tree [Max_N];

void calc_subtr_rec(int curr,int par){
    int curr_sum=1;
    for(int i=0;i<tree[curr].size();i++){
        if(!is_centr[tree[curr][i]] and tree[curr][i]!=par){
            calc_subtr_rec(tree[curr][i],curr);
            curr_sum+=subtr[tree[curr][i]];
        }
    }
    subtr[curr]=curr_sum;
    return;
}

void calc_centroid(int curr_r,int p_cen){
    calc_subtr_rec(curr_r,-1);
    int curr=curr_r;
    int c_par=-1;
    bool f_c;
    while(true){
        f_c=false;
        for(int i=0;i<tree[curr].size();i++){
            if(!is_centr[tree[curr][i]] and tree[curr][i]!=c_par){
                if(subtr[tree[curr][i]]>(subtr[curr_r]/2)){
                    c_par=curr;
                    curr=tree[curr][i];
                    f_c=true;
                    goto end_for;
                }
            }
        }
        end_for:;
        if(!f_c){
            is_centr[curr]=true;
            centroid_tree[curr].push_back(p_cen);
            centroid_tree[p_cen].push_back(curr);
            for(int i=0;i<tree[curr].size();i++){
                if(!is_centr[tree[curr][i]]){
                    calc_centroid(tree[curr][i],curr);
                }
            }
            goto end_centr_constr;
        }
    }
    end_centr_constr:return;
}

void read_input(){
    cin>>n;
    int a,b;
    for(int i=1;i<n;i++){
        cin>>a>>b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    return;
}

/*

8
1 2
1 3
3 4
3 5
4 6
4 7
4 8

*/

int main(){
    ios_base::sync_with_stdio(false);
    read_input();
//    calc_subtr_rec(0,-1);
//    for(int i=0;i<n;i++){
//        cout<<subtr[i]<<endl;
//    }
    calc_centroid(0,-1);
    cout<<"Adjacency list of the centroid tree:"<<endl;
    for(int i=0;i<n;i++){
        cout<<"Vertex number "<<i+1<<" : ";
        for(int j=0;j<centroid_tree[i].size();j++){
            cout<<centroid_tree[i][j]+1<<" ";
        }
        cout<<endl;
    }
    return 0;
}
