#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int MAX_N = 1e5 + 10;
int a[MAX_N],b[MAX_N];
struct node{
    int a,b,len;
}tree[MAX_N<<2],lazy[MAX_N<<2],res;

void build(int k,int l,int r){
    if(l==r)tree[k] ={0,0,0};
    else{
        int mid = (l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
    }
}
void update(int v,int l,int r,int ql,int qr,struct node val){
    if(r<ql || qr<=l) return;
    else if(ql<=l and r<qr){
        tree[v]=val;
        lazy[v]=val;
        //cout<<"JI"<<endl;
    }
    else{
        if(lazy[v].len!=0){
            tree[v<<1] = lazy[v];
            lazy[v<<1] = lazy[v];
            tree[v<<1|1] = lazy[v];
            lazy[v<<1|1] = lazy[v];
            lazy[v] = {0,0,0};
        }
        int mid = (l+r)>>1;
        update(v<<1,l,mid,ql,qr,val);
        update(v<<1|1,mid+1,r,ql,qr,val);
    }
}
struct node query(int v,int l,int r,int pos){
    if(l==r){
        return tree[v];
    }
    if(lazy[v].len!=0){
        tree[v<<1] = lazy[v];
        lazy[v<<1] = lazy[v];
        tree[v<<1|1] = lazy[v];
        lazy[v<<1|1] = lazy[v];
        lazy[v] = {0,0,0};
    }
    int mid = (l+r)>>1;
    if(pos<=mid) return query(v<<1,l,mid,pos);
    else return query(v<<1|1,mid+1,r,pos);
}
int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    build(1,1,n);
    for(int i=0;i<m;i++){
        int op;
        cin >> op;
        if(op == 1){
            int x,y,len;
            cin >> x >> y >> len;
            update(1,1,n,y,y+len,{x,y,len});
            /*
            for(int i=1;i<=19;i++){
                cout<< tree[i].a<<","<<tree[i].b<<","<<tree[i].len<<endl;
            }*/
        }
        else if(op == 2){
            int k;
            cin >> k;
            struct node m = query(1,1,n,k);
            //cout<<"bug"<<m.len<<endl;
            if(m.len!=0) cout<<a[m.a + k -m.b]<<endl;
            else cout<<b[k]<<endl;
        }
    }
}
