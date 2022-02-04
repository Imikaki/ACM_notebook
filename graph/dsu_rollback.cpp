// CSP 13.11.20
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define st first
#define nd second
#define pb push_back
using namespace std;
const int N = 1e5+1;
struct DSU_rollback
{
    vector<int> lab;
    vector<pii> his;
    int n;
    int root(int x)
    {
        if(lab[x] < 0) return x;
        his.pb({x, lab[x]});
        return lab[x] = root(lab[x]);
    }
    bool join(int u,int v)
    {
        u = root(u);
        v = root(v);
        if(u == v) return 0;
        his.pb({u, lab[u]});
        his.pb({v, lab[v]});
        if(lab[u] > lab[v]) swap(u,v);
        lab[u] += lab[v];
        lab[v] = u;
        return 1;
    }
    void rollback(bool ok) /// ok = có đưa các lab bị thay đổi về version cũ ko ?
    {
        if(ok)
        {
            while(his.size())
            {
                lab[his.back().st] = his.back().nd;
                his.pop_back();
            }
        }
        else his.clear();
    }
    DSU_rollback(int n) : n(n), lab(n+1, -1), his(0) {}
};
int main()
{
    int n = 3;
    DSU_rollback dsu(n);
    dsu.join(1,2);
    dsu.rollback(0);

    dsu.join(2,3);

    forinc(i,1,n) cout << dsu.root(i) << ' ';
    cout << endl;

    dsu.rollback(1);

    forinc(i,1,n) cout << dsu.root(i) << ' ';
    cout << endl;
}
