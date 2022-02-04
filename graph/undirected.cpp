// CTP 20.12.20

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back
using namespace std;

typedef pair<int, int> pii;
#define st first
#define nd second

const int N = 5e4+5;

struct edge
{
	int u, v;
	edge() {}
	edge(int u,int v) : u(u), v(v) {}
};

struct graph
{
	int n, ind, sSLT = 0, sBIC = 0, n_hinge = 0, n_bridge = 0;
	vector<vector<int> > ad;
	vector<edge> E;
	vector<int> par, num, low, vis, slt, bic, cbic;
	graph(int n) : n(n), ad(n+1,vector<int>()), slt(n+1), bic(n+1,0), cbic(n+1),
					par(n+1), num(n+1), low(n+1), vis(n+1) {}
	void AddEdge(int u, int v)
	{
		ad[u].pb(E.size());
		ad[v].pb(E.size());
		E.pb(edge(u, v));
	}
	void DFS(int u, int j)
	{
        num[u] = low[u] = ++ind;
        vis[u] = 1;
        for(int i : ad[u]) if(i != j)
		{
			int v = E[i].u + E[i].v - u;
			if(!vis[v])
			{
				par[v] = u;
				DFS(v, i);
				low[u] = min(low[u], low[v]);
			}
			else low[u] = min(low[u], num[v]);
		}
	}
	stack<int> st;
	void SLT(int u,int j)
	{
		st.push(u); vis[u] = 2;
        for(int i : ad[u]) if(i != j)
		{
			int v = E[i].u + E[i].v - u;
			if(par[v] == u && vis[v] != 2) SLT(v, i);
		}
		if(num[u] == low[u])
		{
			int v;
			++sSLT;
			do
			{
				v = st.top(); st.pop();
				slt[v] = sSLT;
			}while(v != u);
		}
	}
	void BIC(int u,int j)
	{
		st.push(u); vis[u] = 3;
		for(int i : ad[u]) if(i != j)
		{
			int v = E[i].u + E[i].v - u;
			if(par[v] == u && vis[v] != 3) BIC(v, i);
		}
		if(par[u] && low[u] >= num[par[u]])
		{
            ++sBIC; cbic[sBIC] = 0;
            int v;
            do
			{
				v = st.top(); st.pop();
				cbic[sBIC]++;
				bic[v]++;
			}while(v != u);
			if(cbic[sBIC]==1 || low[u] == num[par[u]])
			{
				++cbic[sBIC];
				bic[par[u]]++;
			}
		}
	}
	void build()
	{
        forinc(i, 1, n) if(!vis[i])
        {
        	DFS(i, -1);
        	while(!st.empty()) st.pop();
        	SLT(i, -1);
        	while(!st.empty()) st.pop();
        	BIC(i, -1);
        }
        forinc(u, 1, n)
        {
        	if(bic[u] > 1) ++n_hinge;
        	for(int i : ad[u])
			{
				int v = E[i].u + E[i].v - u;
				if(slt[v] != slt[u] && v > u) ++n_bridge;
			}
        }
	}
};


int main()
{
	//freopen("graph.inp","r",stdin);

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
    cin >> n >> m;
    graph g(n);
	int u, v;
	forinc(i, 1, m)
	{
		cin >> u >> v;
		g.AddEdge(u, v);
	}
	g.build();
    cout << g.n_hinge << ' ' << g.n_bridge;
}