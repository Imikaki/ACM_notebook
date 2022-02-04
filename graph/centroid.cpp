// _ruatin_
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pb push_back
using namespace std;
const int N = 1e5+5;

int n, m;
vector<int> ke[N], c[N];
int dd[N], s[N], p[N];

int Find(int u,int p,int cnt)
{
    int vm = 0;
    for(int v:ke[u]) if(v!=p && !dd[v])
    {
        if(s[v] > s[vm]) vm = v;
    }
    if(s[vm] <= cnt/2) return u;
    else return Find(vm, u, cnt);
}

void DFS(int u,int p)
{
    s[u] = 1;
    for(int v:ke[u]) if(v!=p && !dd[v])
    {
        DFS(v,u);
        s[u] += s[v];
    }
}

void build(int u)
{
    dd[u] = 1;
    DFS(u,0);
    for(int t:ke[u]) if(!dd[t])
    {
        int v = Find(t,u,s[t]);
        c[u].pb(v);
        p[v] = u;
    }
    for(int v:c[u]) build(v);
}

int P[N][20], d[N], logn, f[N];
void original(int u)
{
    forinc(i,1,logn) P[u][i] = P[P[u][i-1]][i-1];
    for(int v:ke[u]) if(v != P[u][0])
    {
        P[v][0] = u;
        d[v] = d[u]+1;
        original(v);
    }
}

int lca(int u,int v)
{
    if(d[u] < d[v]) swap(u,v);
    int del = d[u]-d[v];
    forinc(i,0,logn) if((del>>i)&1) u = P[u][i];
    if(u==v) return u;
    fordec(i,logn,0) if(P[u][i] != P[v][i])
    {
        u = P[u][i];
        v = P[v][i];
    }
    return P[u][0];
}

int dist(int u,int v)
{
    int p = lca(u,v);
    return d[u] + d[v] - 2*d[p];
}

void Tree()
{
    forinc(i,1,n-1)
    {
        int u,v;
        cin >> u >> v;
        ke[u].pb(v);
        ke[v].pb(u);
    }
    original(1);
    DFS(1,0);
    build(Find(1,0,n));
}

void update(int v)
{
    int u = v;
    while(u)
    {
        f[u] =  min(f[u], dist(u,v));
        u = p[u];
    }
}

int answer(int v)
{
    int kq = n+1, u = v;
    while(u)
    {
        kq = min(kq, f[u]+dist(u,v));
        u = p[u];
    }
    return kq;
}

int main()
{
//    freopen("342E.inp","r",stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    logn = log2(n);
    Tree();
    memset(f,127,sizeof f);
    update(1);
    while(m--)
    {
        int t, v;
        cin >> t >> v;
        if(t==1) update(v);
        else cout << answer(v) << '\n';
    }
}
