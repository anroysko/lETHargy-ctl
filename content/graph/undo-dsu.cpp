template<class T> struct Undoable_DSU
{
    vector<T> fa, sz;
    vector<pair<T*, T>> sta;
    Undoable_DSU(int n): fa(n)
    {
        iota(all(fa), 0);
        sz.assign(n, 1);
        sta.clear();
    }
    int getfa(int x)
    {
        T res = 0;
        while(x != fa[x]) x = fa[x];
        return x;
    }
    void safechg(T &x, T y) { sta.pb({&x, x}); x = y; }
    bool merge(int x, int y)
    {
        int fx = getfa(x), fy = getfa(y);
        if(fx == fy) return 1;
        if(sz[fx] < sz[fy]) swap(fx, fy);
        safechg(fa[fy], fx);
        safechg(sz[fx], sz[fx] + sz[fy]);
        return 0;
    }
    void get_top() { return sz(sta); }
    void undo(int top)
    {
        while(sz(sta) > top) *sta.back().FI = sta.back().SE, sta.pop_back();
    }
};