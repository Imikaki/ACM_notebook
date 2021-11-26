// Dinic's algorithm

template<class T> struct Dinic {
    struct edge {
        int u, v;
        T c, f;
        edge(int u = 0, int v = 0, T c = 0, T f = 0) :
            u(u), v(v), c(c), f(f) {};
    };

    int n;
    vector<edge> edge_list;
    vector<vector<int>> adj;
    vector<int> d, pt;

    Dinic();
    Dinic(int n) : n(n) {
        edge_list.clear();
        adj.resize(n + 5);
        d.resize(n + 5, 0);
        pt.resize(n + 5, 0);
    }

    void add_edge(int u, int v, T f) {
        if(u == v) return;
        adj[u].push_back(edge_list.size());
        edge_list.push_back(edge(u, v, f, 0));
        adj[v].push_back(edge_list.size());
        edge_list.push_back(edge(v, u, 0, 0));
    }
    bool exist_path(int src, int sink) {
        queue<int> q;
        fill(begin(d), end(d), n * 2);
        d[src] = 0;
        q.push(src);
        while(q.size()) {
            int u = q.front();
            q.pop();
            if(u == sink) break;
            for (int &it : adj[u]) {
                edge &v = edge_list[it];
                if(v.c > v.f && d[v.v] > d[u] + 1) {
                    d[v.v] = d[u] + 1;
                    q.push(v.v);
                }
            }
        }
        return d[sink] != n * 2;
    }
    T dfs(int u, int t, T flow = -1) {
        if(u == t || flow == 0) return flow;
        for (int &i = pt[u]; i < adj[u].size(); ++i) {
            edge &ed = edge_list[adj[u][i]];
            edge &rev_ed = edge_list[adj[u][i] ^ 1];
            if(d[ed.v] == d[ed.u] + 1) {
                T now = ed.c - ed.f;
                if(flow != -1 && now > flow)
                    now = flow;
                if(T pushed = dfs(ed.v, t, now)) {
                    ed.f += pushed;
                    rev_ed.f -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    T max_flow(int s, int t) {
        T ans = 0;
        while(exist_path(s, t)) {
            fill(begin(pt), end(pt), 0);
            while(T flow = dfs(s, t)) {
                ans += flow;
            }
        }
        return ans;
    }
};

