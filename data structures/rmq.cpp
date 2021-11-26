// RMQ, Range Min/Max Query
template <typename T, class func = function<T(const T&, const T&)> >
struct rmq {
    int n;
    vector<vector<T> > b;
    func F;

    rmq(const vector<T> &a, const func &_F) : F(_F) {
        n = (int)a.size();
        int log_size = 0;
        while ((1 << log_size) <= n) log_size++;
        b.resize(log_size);
        b[0] = a;
        for (int j = 1; j < log_size; j++) {
            b[j].resize(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++) {
                b[j][i] = F(b[j - 1][i], b[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T calc(int L, int R) const {
        assert(0 <= L && L <= R && R < n);
        int k = __lg(R - L + 1);
        assert((1 << k) <= (R - L + 1) && (1 << (k + 1)) > (R - L + 1));
        return F(b[k][L], b[k][R - (1 << k) + 1]);
    }
};
