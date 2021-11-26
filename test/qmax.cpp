#include <bits/stdc++.h>

using namespace std;

struct segTree {
    struct node {
        int val;
        int lazy;
        node(): val(0) {}
        node(int val_, int lazy_): val(val_), lazy(lazy_) {}
    };
    void apply(node &x, int l, int r, int v) {
        x.val += v;
        x.lazy += v;
    }
    node unite(int i, node a, node b) {
        node ans;
        // ...
        ans.lazy = tree[i].lazy;
        ans.val = max(a.val, b.val);
        return ans;
    }
    vector<node> tree;
    int n;
    segTree(int n_ = 0) : n(n_) {
        tree.assign(4 * n + 5, node());
    }
    void push(int x, int l, int r) {
        if(tree[x].lazy) {
            int val = tree[x].lazy;
            tree[2 * x].val += val; tree[2 * x + 1].lazy += val;
            tree[2 * x + 1].val += val; tree[2 * x].lazy += val;
            tree[x].lazy = 0;
        }
    }
    void modify(int i, int l, int r, int u, int v, int val) {
        if(v < l || u > r) return;
        if(u <= l && r <= v) {
            apply(tree[i], l, r, val);
            return;
        }
        push(i, l, r);
        int mid = (l + r) / 2;
        modify(2 * i, l, mid, u, v, val);
        modify(2 * i + 1, mid + 1, r, u, v, val);
        tree[i] = unite(i, tree[2 * i], tree[2 * i + 1]);
    }
    node query(int i, int l, int r, int u, int v) {
        if(v < l || u > r) return node();
        if(u <= l && r <= v) return tree[i];
        push(i, l, r);
        int mid = (l + r) / 2;
        return unite(i, query(2 * i, l, mid, u, v), query(2 * i + 1, mid + 1, r, u, v));
    }
};

segTree P;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    P = segTree(n);
    int m; cin >> m;
    while(m--) {
        int t, l, r, k;
        cin >> t >> l >> r;
        if(t == 1) {
            cout << P.query(1, 1, n, l, r).val << '\n';
        } else {
            cin >> k;
            P.modify(1, 1, n, l, r, k);
        }
    }
}
