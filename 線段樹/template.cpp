#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int MAX_N = 2e6 + 10;
int a[MAX_N];
long long int tree[MAX_N>>2];
int tag[MAX_N>>2];

void build(int k,int l,int r){
    tag[k] = 0;
    if(l==r){
        tree[k] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    tree[k] = tree[k>>1] + tree[k>>1|1];
}
void push_down(int tl,int tr,int k){
    int mid = (tr + tl) >> 1;
    tree[k<<1] += tag[k]*(long long int)(mid - tl + 1);
    tag[k<<1] += tag[k];
    tree[k<<1|1] += tag[k]*(long long int)(tr - mid);
    tag[k<<1|1] += tag[k];
    tag[k] = 0;
}
void update(int sl,int sr,int tl,int tr,int k,int delta){
    if(sl <= tl && tr <= sr){
        tree[k] += delta*(long long int)(tr - tl + 1);
        tag[k] += delta;
        return;
    }
    push_down(tl,tr,k);
    int mid = (tl + tr)>>1;
    if(sl <= mid)update(sl,sr,tl,mid,k<<1,delta);
    if(mid < sr)update(sl,sr,mid+1,tr,(k<<1)|1,delta);
    tree[k] = tree[k<<1] + tree[(k<<1)|1];
}
long long int query(int sl,int sr,int tl,int tr,int k){
    if(sl <= tl && tr <= sr) return tree[k];
    long long int ret = 0;
    push_down(tl,tr,k);
    int mid = (tl + tr) >> 1;
    if(sl <= mid) ret += (long long int) query(sl,sr,tl,mid,k<<1);
    if(mid < sr) ret += (long long int)  query(sl,sr,mid+1,tr,(k<<1)|1);
    return ret;
}
int main(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    build(1,1,n);
    for(int i=0;i<m;i++){
        int c;
        cin >> c;
        if(c == 1){
            int x,y;
            long long int z;
            cin >> x >> y >> z;
            update(x,y,1,n,1,z);
        }
        else if(c == 2){
            int x,y;
            cin >> x >> y;
            printf("%lld\n",query(x,y,1,n,1));
        }
    }
}
