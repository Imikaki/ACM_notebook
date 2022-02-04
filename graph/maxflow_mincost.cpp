// CSP 28.11.20
// skyvn97 mincost vnoi

// INPUT:
//     - graph, constructed using AddEdge()
//     - source and sink
//
// OUTPUT:
//     - maximum flow value and minimun cost value
//     - To obtain actual flow values, look at edges with flow > 0


#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)

using namespace std;
const int N = 1001, inf = 2e9;

struct edge
{
    int u, v, cap, flow, cost;
    edge(int u,int v,int ca,int co) : u(u), v(v), cap(ca), flow(0), cost(co) {}
    int residual() {
        return cap - flow;
    }
};

struct MaxFlow_MinCost
{
    vector<vector<int> > g;
    vector<edge> e;
    vector<int> d, pre;
    int n, MaxFlow = 0, MinCost = 0;
    MaxFlow_MinCost(int n) : n(n)
    {
        g.assign(n+1, vector<int>());
        e.clear();
        d.resize(n+1);
        pre.resize(n+1);
    }
    void AddEdge(int u,int v,int ca,int co)
    {
        g[u].push_back(e.size());
        e.push_back(edge(u, v, ca, co));
        g[v].push_back(e.size());
        e.push_back(edge(v, u, 0, -co));
    }
    bool FindPath(int s,int t)
    {
        d.assign(n+1, inf);
        vector<bool> inq(n+1, 0);
        queue<int> q;
        q.push(s); inq[s] = 1; d[s] = 0;
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for(int i : g[u]) if(e[i].residual() > 0)
            {
                int v = e[i].v;
                if(d[v] > d[u]+e[i].cost)
                {
                    d[v] = d[u] + e[i].cost;
                    pre[v] = i;
                    if(!inq[v])
                    {
                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return d[t] < inf;
    }
    void IncFlow(int s,int t)
    {
        int delta = inf;
        for(int u=t; u!=s; u=e[pre[u]].u)
            delta = min(delta, e[pre[u]].residual());
        for(int u=t; u!=s; u=e[pre[u]].u)
        {
            e[pre[u]].flow += delta;
            e[pre[u]^1].flow -= delta;
        }
        MaxFlow += delta;
        MinCost += delta*d[t];
    }
    pair<int,int> GetFlow(int s,int t)
    {
        while(FindPath(s, t)) IncFlow(s, t);
        return {MaxFlow, MinCost};
    }
    void PrinfFlow(int s,int t)
    {
        cout << GetFlow(s,t).second << '\n';
        forinc(i,0,e.size()-1) if((i%2==0) && e[i].flow>0)
            cout << e[i].u << ' ' << e[i].v << ' ' << e[i].flow << '\n';
    }
};
int capa[N][N], cost[N][N];
int main()
{
    //freopen("mincost.inp","r",stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m, k, s, t;
    cin >> n >> m >> k >> s >> t;
	memset(capa,-1,sizeof capa);
	while(m--){
		int u,v,c,d;
		cin >> u >> v >> c >> d;
		capa[u][v]=d;
		cost[u][v]=c;
		capa[v][u]=d;
		cost[v][u]=c;
	}
	MaxFlow_MinCost g(n+5);
	forinc(u,1,n) forinc(v,1,n) if (capa[u][v]>=0) g.AddEdge(u,v,capa[u][v],cost[u][v]);
	g.AddEdge(0,s,k,0);
    if(g.GetFlow(0,t).first < k) return cout << -1,0;
    g.PrinfFlow(0,t);
    cout << "0 0 0";
}