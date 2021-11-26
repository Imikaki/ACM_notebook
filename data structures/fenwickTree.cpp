template<typename T> struct fenwick {
    vector<T> it;
    int n;
    fenwick(int n_ = 0): n(n_) {
        it.assign(n + 5, 0);
    }
    void modify(int x, T v) {
        while(x <= n) {
            it[x] += v;
            x += x & -x;
        }
    }
    T get(int x) {
        T ans = 0;
        while(x) {
            ans += it[x];
            x -= x & -x;
        }
        return ans;
    }
};
