/*查找区间第k小*/
const int MAXN = 200005;
const int MAXM = 22;

struct Info {
    Info* l = nullptr;
    Info* r = nullptr;
    ll sum = 0;
};
Info* ptrs = new Info[MAXN * MAXM];
ll tot = 0;
class SegTree {
public:
    ll n;
    vector<Info*> roots;
    explicit SegTree(ll n_): n(n_) {roots.assign(n_ + 1, nullptr);}
    void bulidroot(Info* &x, ll l, ll r) {
        tot++;
        x = ptrs + tot;
        if (l == r) return;
        ll m = (l + r) >> 1;
        bulidroot(x->l, l, m);
        bulidroot(x->r, m + 1, r);
    }
    void bulidroot() {
        bulidroot(roots[0], 1, n);
    }

    void init(Info* &cur, Info* pre, ll l, ll r, ll v) {
        cur = ptrs + (++tot);
        *cur = *pre;
        cur->sum++;
        if (l == r) return;
        ll m = (l + r) >> 1;
        if (v <= m) init(cur->l, pre->l, l, m, v);
        else init(cur->r, pre->r, m + 1, r, v);
    }

    template<typename Array>
    void init(Array &data) {
        bulidroot();
        for (int i = 1; i <= n; i++) {
            init(roots[i], roots[i - 1], 1, n, data[i - 1]);
        }
    }
    ll ask(Info* cur, Info* pre, ll l, ll r, ll v) {
        if (l == r) return l;
        ll m = (l + r) >> 1;
        ll s = cur->l->sum - pre->l->sum;
        if (s >= v) return ask(cur->l, pre->l, l, m, v);
        else return ask(cur->r, pre->r, m + 1, r, v - s);
    }
    ll ask(ll ql, ll qr, ll v) {
        return ask(roots[qr], roots[ql - 1], 1, n, v);
    }

};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<ll> csa(n);
    vector<ll> sorta(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorta[i] = a[i];
    }
    sort(sorta.begin(), sorta.end());
    // auto inisa = sorta;
    sorta.erase(unique(sorta.begin(), sorta.end()), sorta.end());
    for (int i = 0; i < n; i++) {
        csa[i] = lower_bound(sorta.begin(), sorta.end(), a[i]) - sorta.begin() + 1;
    }
    // printvec(inisa);
    // printvec(csa);
    SegTree seg(n);
    seg.init(csa);
    // 处理查询
    while (q--) {
        int l, r, c;
        cin >> l >> r >> c;
        ll ind = seg.ask(l, r, c) - 1;
        // cout << "IND " << ind <<" ";
        ll ans = sorta[ind];
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    //cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
