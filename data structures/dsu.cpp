#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
    vector<int> p;
    int n;
    dsu(int _n): n(_n) {
        p.resize(n + 5);
        iota(begin(p), end(p), 0);
    }
    int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }
    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if(x != y) {
            p[x] = y;
            return true;
        } else 
            return false;
    }
};

int main() {
    
}