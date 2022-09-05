#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int C[205][205],level[205];
const int inf = 0x3f3f3f3f;
int n,m;
void bfs(int u){
    queue<int> q;
    q.push(u);
    do{
        u = q.front();
        q.pop();
        for(int i=1;i<=m;i++){
            if(C[u][i] > 0 && level[i] == -1){
                q.push(i);
                level[i] = level[u]+1;
            }
        }
    }while(q.empty()!=true);
    /*
    for(int i=0;i<=m;i++){
        cout<<level[i] << " ";
    }*/
    //cout<<endl;
}
int dfs(int u,int flow){
    int ret = 0;
    if(u==m) return flow;
    for(int i=1;i<=m;i++){
        if(C[u][i] > 0 && level[i] > level[u]){
            //cout<<"外面"<<i<<endl;
            int f= dfs(i,min(flow,C[u][i]));
            //cout<<"i"<<i<<"---f"<<f<<endl;
            C[u][i] -= f;
            C[i][u] += f;
            ret += f;
            flow-=f;
        }
    }

    return ret;
}
int main(){
    while(cin >> n >> m){
        memset(C,0,sizeof(C));
        for(int i=0;i<n;i++){
            int u,v,c;
            cin >> u >> v >> c;
            C[u][v] += c;
        }
        int ans = 0,ret = 0;
        do{
            //cout<<"HI"<<endl;
            for(int i=0;i<=m;i++){
                level[i] = -1;
            }
            level[1] = 0;
            bfs(1);
            for(int i=2;i<=m;i++)
                if(C[1][i]>0){
                    ret = dfs(1,C[1][i]);
                    ans += ret;
                }
        }while(level[m]!=-1);
        cout<<ans<<endl;
    }
    return 0;
}
