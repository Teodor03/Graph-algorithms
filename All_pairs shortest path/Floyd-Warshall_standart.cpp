#include<iostream>
using namespace std;

const int Max_N=10000;
const int Inf=999999999;

int n,m;

int d[Max_N][Max_N];

void init(){
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(i==j){
            d[j][i]=0;
        }else{
            d[j][i]=Inf;
        }
    }
}
return;
}

int _min(int a,int b){
    if(a<b){
        return a;
    }
    return b;
}

//can work for negative weights too
void floyd_warshall(){
for(int k=0;k<n;k++){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(d[i][k]!=Inf and d[k][j]!=Inf){
                d[i][j]=_min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}
return;
}

/*

4 6
1 2 1
1 3 1000
1 4 1000
2 3 2
2 4 5
3 4 1

*/

int main(){
cin>>n>>m;
init();
int a,b,c;
for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--;
    b--;
    d[a][b]=c;
}
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        cout<<d[j][i]<<" ";
    }
    cout<<endl;
}
return 0;
}
