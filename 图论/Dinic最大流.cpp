#include <bits/stdc++.h>
#define ll long long
#define PII pair<ll, ll>
using namespace std;
const ll inf = 1e18 + 9;
const ll N = 1e2 + 5;
const ll M = 1e4 + 9;
void printvec(vector<ll> vec) { for (auto it = vec.begin(); it != vec.end(); ++it) { cout << *it << " ";} cout << endl;}
void print2dvec(const vector<vector<ll>>& vec) { for (const auto& row : vec) { for (const auto& element : row) { cout << element << " ";} cout << endl;}}
void printmap(const map<ll, vector<ll>>& g) {for (const auto& [key, value] : g) { cout << "key: " << key << " -> "; for (const auto& v : value) {cout << v << " ";} cout << endl;}}
ll dep[N], head[M], to[M], from[M], w[M], nxt[M];
ll cur[N];
ll ecnt = 0;
ll s, t;
void adde(ll x, ll y, ll z) {
    from[ecnt] = x;
    to[ecnt] = y;
    w[ecnt] = z;
    nxt[ecnt] = head[x];
    head[x] = ecnt++;
}
bool bfs() {
    queue<ll> q;
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof cur);
    dep[s] = 1;
    q.push(s);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = nxt[i]) {
            ll v = to[i];
            if (dep[v] == -1 and w[i] > 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return dep[t] != -1;
}

ll dfs(ll u, ll low) {
    if (u == t) return low;
    ll ret = low;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        ll v = to[i];
        if (dep[v] == dep[u] + 1 && w[i] > 0) {
            ll flow = dfs(v, min(ret, w[i]));
            if (flow > 0) {
                w[i] -= flow;
                w[i ^ 1] += flow;
            }
            ret -= flow;
            if (ret == 0) break;
        }
    }
    return low - ret;
}
ll dinic() {
    ll tmp = 0;
    while (bfs()) {
        tmp += dfs(s, inf);
    }
    return tmp;
}
void MIKUUUUUU() {
    memset(head, -1, sizeof head);
    ll n, m;
    cin >> m >> n;
    s = 0, t = n + 1;
    for (int i = 1; i <= m; i++) {
        adde(s, i, 1);
        adde(i, s, 0);
    }
    for (int i = m + 1; i <= n; i++) {
        adde(i, t, 1);
        adde(t, i, 0);
    }
    while (1) {
        ll u, v;
        cin >> u >> v;
        if (u != -1) {
            adde(u, v, 1);
            adde(v, u, 0);
        }
        else break;
    }
    ll MIKU = dinic();
    cout << MIKU << endl;
    // vector<PII> MIKU;
    for (int i = 0; i < ecnt; i++) {
        if (from[i] >= 1 && from[i] <= m && to[i] > m && w[i] == 0) cout << from[i] << " " << to[i] << endl;
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // int tt; cin >> tt; while (tt--)
    MIKUUUUUU();
    return 0;
}