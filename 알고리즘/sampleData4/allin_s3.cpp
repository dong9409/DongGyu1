#include <bits/stdc++.h>
using namespace std;

typedef struct Time{
    int buy;
    int sell;
}T;

int d(T &t,vector<int>& P) {return P[t.sell]-P[t.buy];}

T Mid(int s,int e, vector<int>& P)
{
    T t;
    int m=(s+e)/2;

    int left=m,right=m,diff=-1;
    for(int i=m;i>=s;i--)
    if(P[m]-P[i] > diff) {diff=P[m]-P[i]; left=i;}
    diff=-1;
    for(int i=m;i<=e;i++)
        if(P[i]-P[m] > diff) {diff=P[i]-P[m]; right=i;}

    t.buy=left;
    t.sell=right;
    return t;
}

T Solve(int s, int e, vector <int>& P)
{
    T t;
    if(s==e){t.buy=s; t.sell=e;}
    else{
        T lt,mt,rt;
        lt=Solve(s,(e+s)/2,P);
        rt=Solve((e+s)/2+1,e,P);
        mt=Mid(s,e,P);
        if(d(lt,P)<d(mt,P) && d(rt,P)<d(mt,P)) t=mt;
        else if(d(rt,P)<d(lt,P)) t=lt;
        else t=rt;
    }
    return t;
}

int main(){
    vector <int> price;
    ifstream ifp("allin.inp");
    ofstream ofp("allin.out");

    int N;
    ifp>>N;
    for(int i=0;i<N;i++)
    {
        int p;
        ifp>>p;
        price.push_back(p);
    }

    T t= Solve(0,N-1,price);
    if(t.buy==t.sell) t.buy=t.sell-1;
    ofp<<t.buy+1<<" "<<t.sell+1;

    ifp.close();
    ofp.close();
    return 0;
}