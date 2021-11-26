#include <bits/stdc++.h>

using namespace std;

template<typename T> struct fenwick {
    vector<T> it;
    int n;
    fenwick(int n_ = 0): n(n_) {
        it.assign(n + 5, 0);
    }
    void modify(int x, T v) {
        while(x <= n) {
            it[x] = max(it[x], v);
            x += x & -x;
        }
    }
    T get(int x) {
        T ans = 0;
        while(x) {
            ans = max(ans, it[x]);
            x -= x & -x;
        }
        return ans;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    fenwick<long long> f(n);
    vector<int> a(n);
    vector<int> x(n);
    for (auto &i : a) cin >> i;
    for (auto &i : x) cin >> i;
    vector<int> b = a;
    sort(begin(b), end(b)); b.erase(unique(begin(b), end(b)), end(b));
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int u = lower_bound(begin(b), end(b), a[i]) - begin(b) + 1;
        auto p = f.get(u - 1);
        ans = max(ans, p + 1ll * x[i]);
        f.modify(u, p + 1ll * x[i]);
    }
    cout << ans << '\n';
}

