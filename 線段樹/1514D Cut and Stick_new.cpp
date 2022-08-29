#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
using namespace std;
const int MAX_N = 3e5 + 10;
struct node{
    int l,r,val;
}tree[MAX_N<<2];
int a[MAX_N];
vector<int> pos[MAX_N];
int get_num(int val,int l,int r){
    return upper_bound(pos[val].begin(),pos[val].end(),r) -
            lower_bound(pos[val].begin(),pos[val].end(),l);
}
void push_up(int k){
    int l = tree[k].l , r= tree[k].r;
    if(get_num(tree[k<<1].val,l,r) > get_num(tree[k<<1|1|1].val,l,r)){
        tree[k].val = tree[k<<1].val;
    }
    else{
        tree[k].val = tree[k<<1|1].val;
    }
}
void build(int k,int l,int r){
    tree[k] = {l,r};
    if(l==r){
        tree[k].val = a[l];
    }
    else{
        int mid = (l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        push_up(k);
    }
}
int query(int k,int l,int r){
    if(l <= tree[k].l && tree[k].r <= r){
        return get_num(tree[k].val,l,r);
    }
    else if(tree[k].l > r || tree[k].r < l){
        return 0;
    }
    else{
        return max(query(k<<1,l,r),query(k<<1|1,l,r));
    }
}
int main(){
    int n,q;
    scanf("%d %d",&n,&q);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[a[i]].push_back(i);
    }
    build(1,1,n);
    for(int i=0;i<q;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",max(1,query(1,l,r)*2 - (r-l+1)));
    }
}
