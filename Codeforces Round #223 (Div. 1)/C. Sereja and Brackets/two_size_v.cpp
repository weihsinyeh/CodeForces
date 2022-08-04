#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define x first;
#define y second;
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> node;
const int MAX_N = 1e7 + 10;
int n;
char s[MAX_N];
int c[MAX_N],o[MAX_N],t[MAX_N];

int segment(int xx,int yy,int l = 1,int r = n){
    if(yy<l && xx >= r) return 0;
    if(xx<l) xx = l;
    if(yy>r) yy = r;
    xx += (n-2);
    yy += (n-2);
    int lT=0,lO=0,lC=0,rT=0,rO=0,rC=0;
    for(; xx < yy; xx >>=1, yy>>=1){
        if(xx&1){
            int tmp = min (c[xx],lO);
            lT = lT + t[xx] + tmp;
            lO = lO + o[xx] - tmp;
            lC = lC + c[xx] - tmp;
            xx++;
        }
        if(yy&1){
            yy--;
            int tmp = min (o[yy],rC);
            rT = rT + t[yy] + tmp;
            rO = rO + o[yy] - tmp;
            rC = rC + c[yy] - tmp;
        }
    }
    return lT + rT + min(lO,rC);
}
void build(){
    for(int i=0;i<n;i++){
        if(s[i+1]=='(')
            o[i+(n-1)] = 1;
        else
            c[i+(n-1)] = 1;
    }
    for(int i = (n-2);i >0;--i){
        int tmp = min(o[i<<1],c[i<<1 | 1]);
        t[i] = t[i<<1] + t[i<<1|1] + tmp;
        o[i] = o[i<<1] + o[i<<1|1] - tmp;
        c[i] = c[i<<1] + c[i<<1|1] - tmp;
    }
}
int main(){
    memset(c,0,sizeof(c));
    memset(o,0,sizeof(o));
    memset(t,0,sizeof(t));
    string input;
    cin >> input;
    n = input.size()+1;
    for(int i=1;i<n;i++)
        s[i] = input[i-1];
    build();
    int op;
    scanf("%d",&op);
    while(op--){
        int xx,yy;
        scanf("%d %d",&xx,&yy);
        printf("%d\n",2*segment(xx,yy+1));
    }
}
