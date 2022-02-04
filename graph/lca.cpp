// pwalk vnoi
#include <bits/stdc++.h>
#define int long long
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N=1e3+1;
vector<int> ke[N];
int n,q;
struct edge{int u,v,c;};
edge e[N];
int p[N][11],d[N],h[N];
void DFS(int u)
{
    forinc(i, 1, log2(n)) p[u][i] = p[p[u][i-1]][i-1];
    for(int i : ke[u])
    {
        int v = i>0 ? e[i].v : e[-i].u;
        if(v == p[u][0]) continue;
        p[v][0] = u;
        d[v] = d[u] + e[abs(i)].c;
        h[v] = h[u] + 1;
        DFS(v);
    }
}
int lca(int u,int v)
{
    if(h[u] < h[v]) swap(u, v);
    int delta = h[u] - h[v];
    forinc(i, 0, log2(delta)+1) if((delta>>i)&1) u = p[u][i];
    if(u == v) return u;
    fordec(i, log2(n), 0) if(p[u][i] != p[v][i])
    {
        u = p[u][i];
        v = p[v][i];
    }
    return p[u][0];
}
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>q;
    forinc(i,1,n-1)
    {
        int u,v,c;
        cin>>u>>v>>c;
        ke[u].push_back(i);
        ke[v].push_back(-i);
        e[i]={u,v,c};
    }
    dfs(1);
    while(q--)
    {
        int u,v;
        cin>>u>>v;
        int w=lca(u,v);
        int res=d[u]-d[w]+d[v]-d[w];
        cout<<res<<'\n';
    }
}
