#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> node;
const int MAX_N = 1e7 + 10;
int n;
int t[MAX_N],o[MAX_N],c[MAX_N];
char s[MAX_N];
node segment(int x,int y,int id = 1,int l = 1,int r = n){
    if(l >= y || x >= r) return node(0,pii(0,0));
    if(x <= l && r <= y)
        return node(t[id],pii(o[id],c[id]));
    int mid = (l + r)/2;
    node a = segment(x,y,2*id,l,mid);
    node b = segment(x,y,2*id + 1,mid,r);
    int T,temp,O,C;
    temp = min(a.y.x , b.y.y);
    T = a.x + b.x + temp;
    O = a.y.x + b.y.x - temp;
    C = a.y.y + b.y.y - temp;
    return node(T,pii(O,C));
}
void build(int id = 1,int l = 1,int r = n){
    if(r - l < 2){
        if(s[l] == '('){
            o[id] = 1;
        }
        else{
            c[id] = 1;
        }
        return;
    }
    int mid = (l + r)/2;
    build(2*id,l,mid);
    build(2*id+1,mid,r);
    int tmp = min(o[2*id],c[2*id+1]);
    t[id] = t[2*id] + t[2*id+1] + tmp;
    o[id] = o[2*id] + o[2*id+1] - tmp;
    c[id] = c[2*id] + c[2*id+1] - tmp;
}
int main(){
    string input;
    cin >> input;
    n = input.size()+1;
    for(int i=1;i<=n;i++){
        s[i] = input[i-1];
    }
    int numOp;
    memset(t,0,sizeof(t));
    memset(o,0,sizeof(o));
    memset(c,0,sizeof(c));
    build();
    scanf("%d",&numOp);
    while(numOp--){
        int xx,yy;
        scanf("%d %d",&xx,&yy);
        node ans = segment(xx,yy+1);
        printf("%d\n",2*ans.x);
    }
}
