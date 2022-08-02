#include<iostream>
#include<cstdio>
#define XOR 1
#define OR 0
using namespace std;
const int MAX_N = 1e6+10;
int tree[3 * MAX_N];
int element[MAX_N];

int perform(int a,int op,int b){
    switch(op){
        case OR: return (a|b);
        case XOR:return (a^b);
    }
}
int other(int op){
    return (op+1)&1;
}
void build(int node,int start,int end,int op){
    if(start == end){
        tree[node] = element[start];
        return;
    }
    int mid = (start + end)/2;
    build(2*node,start,mid,other(op));
    build(2*node+1,mid+1,end,other(op));
    tree[node] = perform(tree[2*node],op,tree[2*node+1]);
}
void update(int node,int start,int end,int index,int value,int op){
    if(start == end){
        tree[node] = element[index] = value;
        return;
    }
    int mid = (start + end)/2;
    if(index >= start && index <= mid)
        update(2*node,start,mid,index,value,other(op));
    else if(index > mid && index <= end)
        update(2*node+1,mid + 1,end,index,value,other(op));
    tree[node] = perform(tree[2*node],op,tree[2*node+1]);
}
int main(){
    int n,queries;
    scanf("%d %d",&n,&queries);
    int numElement = (1 << n);
    for(int i = 1;i <= numElement;i++)//從1開始，比較好處理
        scanf("%d",&element[i]);
    int firstOp = (n%2 == 0 ? XOR:OR);  //最下面那一層要是OR
    build(1,1,numElement,firstOp);
    while(queries--){
        int index,value;
        scanf("%d %d",&index,&value);
        update(1,1,numElement,index,value,firstOp);
        printf("%d\n",tree[1]);
    }
    return 0;
}

