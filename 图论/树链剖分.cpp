#include <bits/stdc++.h>
#define ll long long
#define int long long
#define PII pair<ll, ll>
using namespace std;
const ll inf = 1e18 + 9;

inline void rd(ll &x) {x = 0; short f = 1; char c = getchar(); while ((c < '0' || c > '9') && c != '-') c = getchar(); if (c == '-') f = -1, c = getchar(); while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar(); x *= f;}
inline void pt(ll x) {if (x < 0) putchar('-'), x = -x; if (x > 9) pt(x / 10); putchar(x % 10 + '0');}
struct Tag {
    int v = 0;

    void operator+=(const Tag &t) {
        if (t.v != 0) {
            v += t.v;
        }
    }
};

struct Info {
    int val = 0;
    int l, r;
    Info operator+(const Info &o) const {
        Info res;
        res.val = val + o.val;
        res.l = l;
        res.r = o.r;
        return res;
    }

    void operator+=(const Tag &t) {
        if (t.v != 0) {
            val += t.v * (r - l + 1);
            // cout << "cur "  <<l<< " " << r << endl;
        }
    }
};

struct SegTree {
    vector<Info> info;
    vector<Tag> tag;
    int n;

    explicit SegTree(int n_) : n(n_), info(n_ * 4 + 1), tag(n_ * 4 + 1) {}

    // 打印树信息
    void print_tree(int x = 1, int l = 1, int r = -1) {
        if (r == -1) {
            r = n;  // 默认值为 n
        }

        // 打印当前节点信息
        cout << "Node " << x << " [l=" << info[x].l << ", r=" << info[x].r << "] "
             << "info: " << info[x].val << ", tag: " << tag[x].v << endl;

        if (l == r) {
            // 叶子节点，不再递归
            return;
        } else {
            int mid = (l + r) / 2;
            print_tree(x * 2, l, mid);  // 打印左子树
            print_tree(x * 2 + 1, mid + 1, r);  // 打印右子树
        }
    }

    // 初始化树
    template<typename Array>
    void init(int x, int l, int r, Array &data) {
        info[x].l = l;
        info[x].r = r;
        if (l == r) {
            info[x].val = data[l];  // 初始化叶子节点
        } else {
            int mid = (l + r) / 2;
            init(x * 2, l, mid, data);
            init(x * 2 + 1, mid + 1, r, data);
            pull_up(x);  // 更新父节点
        }
    }

    template<typename Array>
    void init(Array &data) {
        init(1, 1, n, data);
    }

    // 懒标记的应用
    void apply(int x, const Tag &v) {
        if (v.v != 0) {
            info[x] += v;
            // cout << x << " "<<info[x].l << " " << info[x].r <<endl;
        }
        tag[x] += v;  // 将懒标记传递给子节点
    }

    // 推送懒标记
    void push_down(int x) {
        int l = info[x].l;
        int r = info[x].r;
        if (tag[x].v != 0) {
            // 将懒标记传递给左右子树
            if (l != r) {
                apply(x * 2, tag[x]);
                apply(x * 2 + 1, tag[x]);
            }
            // 清空当前节点的懒标记
            tag[x] = {};
        }
    }

    // 更新父节点信息
    void pull_up(int x) {
        push_down(x);
        info[x] = info[x * 2] + info[x * 2 + 1];  // 父节点更新为左右子树的合并
    }

    // 区间更新
    void update(int x, int l, int r, int lq, int rq, const Tag &v) {
        push_down(x);  // 先处理懒标记
        if (lq <= l && rq >= r) {
            // 当前区间完全覆盖更新区间
            apply(x, v);
        } else if (lq > r || rq < l) {
            // 当前区间不相交
            return;
        } else {
            int mid = (l + r) / 2;
            update(x * 2, l, mid, lq, rq, v);  // 更新左子树
            update(x * 2 + 1, mid + 1, r, lq, rq, v);  // 更新右子树
            pull_up(x);  // 更新父节点
        }
    }

    void update(int lq, int rq, const Tag &v) {
        update(1, 1, n, lq, rq, v);
    }

    // 修改单个元素
    void modify(int x, int l, int r, int pos, int v) {
        push_down(x);
        if (l == r) {
            info[x].val += v;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            modify(x * 2, l, mid, pos, v);  // 更新左子树
        } else {
            modify(x * 2 + 1, mid + 1, r, pos, v);  // 更新右子树
        }
        pull_up(x);  // 更新父节点
    }

    void modify(int pos, int v) {
        modify(1, 1, n, pos, v);
    }

    // 区间查询
    Info ask(int x, int l, int r, int lq, int rq) {
        push_down(x);
        if (lq <= l && rq >= r) {
            return info[x];
        } else if (lq > r || rq < l) {
            return Info{};
        } else {
            int mid = (l + r) / 2;
            auto ans = ask(x * 2, l, mid, lq, rq) + ask(x * 2 + 1, mid + 1, r, lq, rq);
            return ans;
        }
    }

    Info ask(int lq, int rq) {
        return ask(1, 1, n, lq, rq);
    }

    template<typename CheckFun>
    int find(int x, int l, int r, int lq, int rq, Info &sum, CheckFun &&check) {
        push_down(x);
        if (lq <= l && rq >= r) {
            auto sum_t = sum + info[x];
            if (!check(sum_t)) {
                sum = sum_t;
                return -1;
            }
            if (l == r) {
                return l;
            }
        } else if (lq > r || rq < l) {
            return -1;
        }
        int mid = (l + r) / 2;
        int ans = find(x * 2, l, mid, lq, rq, sum, check);
        return (ans != -1) ? ans : find(x * 2 + 1, mid + 1, r, lq, rq, sum, check);
    }

    template<typename CheckFun>
    int find(int lq, int rq, CheckFun &&check) {
        Info sum = {};
        return find(1, 1, n, lq, rq, sum, check);
    }
};
void printvec(vector<ll> vec) { for (auto it = vec.begin(); it != vec.end(); ++it) { cout << *it << " ";} cout << endl;}
void print2dvec(const vector<vector<ll>>& vec) { for (const auto& row : vec) { for (const auto& element : row) { cout << element << " ";} cout << endl;}}
void printPII(vector<PII> vec) { for (auto it = vec.begin(); it != vec.end(); ++it) { cout << (*it).first << "->" << (*it).second << " ";} cout << endl;}
void printPIII(vector<pair<ll, PII>> vec) { for (auto it = vec.begin(); it != vec.end(); ++it) { cout << (*it).second.first << "/" << (*it).second.second << "\n";}}
void printvecmap(const map<ll, vector<ll>>& g) {for (const auto& [key, value] : g) { cout << "key: " << key << " -> "; for (const auto& v : value) {cout << v << " ";} cout << endl;}}
void printmap(const map<ll, ll>& g) { for (const auto& [key, value] : g) { cout << "key: " << key << " -> " << value << " ";} cout << endl;}

void MIKUUUUUU() {
    ll n, q, r;
    cin >> n >> q >> r;
    vector<ll> w(n + 1);
    vector<vector<ll>> g(n + 1);
    for (int i = 1; i < n + 1; i++)  cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> sz(n + 1);
    vector<ll> deps(n + 1);
    vector<ll> fas(n + 1);
    vector<ll> mxson(n + 1);
    function<void(ll, ll)> pdfs = [&] (ll u, ll f) {
        deps[u] = deps[f] + 1;
        fas[u] = f;
        sz[u] = 1;
        ll mx = 0;
        for (auto v : g[u]) {
            if (v == f) continue;
            pdfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > mx) {
                mxson[u] = v;
                mx = sz[v];
            }
        }

    };
    vector<ll> dfsids(n + 1);
    vector<ll> enddfsids(n + 1);
    vector<ll> tops(n + 1);
    vector<ll> weis(n + 1);
    ll tot = 1;
    SegTree seg(n);
    function<void(ll, ll)> pdfs2 = [&] (ll u, ll top) {
        tops[u] = top; dfsids[u] = tot; weis[tot] = w[u]; tot++;
        if (mxson[u]) pdfs2(mxson[u], top);
        for (auto v : g[u]) {
            if (v == fas[u] || v == mxson[u]) continue;
            pdfs2(v, v);
        }
        enddfsids[u] = tot - 1;
    };
    pdfs(r, 0);
    pdfs2(r, r);
    seg.init(weis);
//     printvec(weis);
//     printvec(dfsids);
//      printvec(fas);
//     printvec(enddfsids);
//     seg.print_tree();
    while (q--) {
        ll op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            seg.modify(dfsids[x], y);
        }
        else if (op == 2) {
            seg.update(dfsids[x], enddfsids[x], Tag{y});
        }
        else {
            ll miku = 0;
            while (tops[x] != tops[y]) {
                if (deps[tops[x]] < deps[tops[y]]) swap(x, y);
                miku += seg.ask(dfsids[tops[x]], dfsids[x]).val;
                x = tops[x];
                x = fas[x];
            }
            if (deps[x] < deps[y]) swap(x, y);
            miku += seg.ask(dfsids[y], dfsids[x]).val;
            cout << miku << endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//     int tt; cin >> tt; while (tt--)
    MIKUUUUUU();
    return 0;
}
