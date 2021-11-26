#define ii pair<int, int>
#define fi first
#define se second

struct edge
{
    int u, v, c, f, d;
    edge ()
    {
        u = v = c = f = d = 0;
    };
    edge (int _u, int _v, int _c, int _f, int _d) :
        u(_u), v(_v), c(_c), f(_f), d(_d) {};
};
struct mincost
{
    int n;
    vector<vector<int>> adj;
    vector<edge> e;
    vector<int> dist, trace, inqueue;

    mincost() {};
    mincost(int n) : n(n)
    {
        adj.clear();
        e.clear();
        dist.clear();
        trace.clear();
        adj.resize(n + 5);
        dist.resize(n + 5, 0);
        trace.resize(n + 5, 0);
        inqueue.resize(n + 5, 0);
    };
    void add_edge(int u, int v, int f, int cost)
    {
        adj[u].pb(e.size());
        e.pb(edge(u, v, f, 0, cost));
        adj[v].pb(e.size());
        e.pb(edge(v, u, 0, 0, -cost));
    }
    bool bfs(int s, int t)
    {
        fill(begin(dist), end(dist), inf);
        fill(begin(trace), end(trace), -1);
        fill(begin(inqueue), end(inqueue), 0);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        inqueue[s] = 1;
        while(q.size())
        {
            int u = q.front();
            q.pop();
            inqueue[u] = false;
            for (int &it : adj[u])
            {
                if(e[it].c - e[it].f > 0)
                {
                    int v = e[it].v;
                    if(dist[v] > dist[u] + e[it].d)
                    {
                        dist[v] = dist[u] + e[it].d;
                        trace[v] = it;
                        if(!inqueue[v])
                        {
                            q.push(v);
                            inqueue[v] = true;
                        }
                    }
                }
            }
        }
        return dist[t] < inf;
    }
    ii max_flow(int s, int t)
    {
        int ans = 0;
        int ans_cost = 0;
        while(bfs(s, t))
        {
            int delta = 2 * inf;
            for (int u = t; u != s; u = e[trace[u]].u)
            {
                delta = min(delta, e[trace[u]].c - e[trace[u]].f);
            }
            for (int u = t; u != s; u = e[trace[u]].u)
            {
                e[trace[u]].f += delta;
                e[trace[u] ^ 1].f -= delta;
            }
            ans += delta;
            ans_cost += delta * dist[t];
        }
        return make_pair(ans, ans_cost);
    }
};
