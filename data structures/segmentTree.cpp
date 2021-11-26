struct segTree {
    struct node {
        int val;
        int lazy;
        node(): val(0) {}
        node(int val_, int lazy_): val(val_), lazy(lazy_) {}
    };
    void apply(node &x, int l, int r, int v) {

    }
    node unite(node a, node b) {
        node ans;
        // ...
        return ans;
    }
    vector<node> tree;
    int n;
    segTree(int n_ = 0) : n(n_) {
        tree.assign(4 * n + 5, node());
    }
    void push(int x, int l, int r) {
        if(tree[x].lazy) {

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
        tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
    }
    node query(int i, int l, int r, int u, int v) {
        if(v < l || u > r) return node();
        if(u <= l && r <= v) return tree[i];
        push(i, l, r);
        int mid = (l + r) / 2;
        return unite(query(2 * i, l, mid, u, v), query(2 * i + 1, mid + 1, r, u, v));
    }
};
