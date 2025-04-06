// 初音未来-纳西妲-芙宁娜第一可爱喵
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define ne " -> "
#define sep "======"
#define fastio ios::sync_with_stdio(false);cin.tie(0);
#define fill(a) iota(a.begin(), a.end(), 0)
#define all(a) a.begin(), a.end()
// 交互题记得注释
#define endl '\n'

typedef long long ll;
typedef pair<long long, long long> PLL;
typedef tuple<ll, ll, ll> TLLL;
//const ll inf =  0x3f3f3f3f;
const ll INF = (ll)2e18 + 9;
const ll MOD = 1000000007;
//const ll MOD = 998244353;
inline void rd(ll &x) {x = 0; short f = 1; char ch = getchar(); while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();} while (isdigit(ch)) {x = (x << 3) + (x << 1) + (ch ^ 0x30); ch = getchar();} x *= f;}
inline ll read() {ll x = 0; short f = 1; char ch = getchar(); while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();} while (isdigit(ch)) {x = (x << 3) + (x << 1) + (ch ^ 0x30); ch = getchar();} x *= f; return x}
inline void pt(ll x) {if (x < 0) putchar('-'), x = -x; if (x > 9) pt(x / 10); putchar((x % 10) | 0x30);}
inline void print(ll x) {pt(x), puts("");}
inline void printPLL(PLL x) {pt(x.fi), putchar(' '), pt(x.se), putchar('\n');}
inline void printVec(vector<ll> &vec) {for (const auto t : vec)pt(t), putchar(' '); puts("");}
inline void printMap(const map<ll, ll>& g) {for (const auto& [key, value] : g) {cout << "key: " << key << ne << value << " ";} puts("");}
inline void printVPLL(vector<PLL> &vec) {puts(sep); for (const auto v : vec) {printPLL(v);} puts(sep);}
inline void printVecMap(const map<ll, vector<ll>>& g) {for (const auto& [key, value] : g) { cout << "key: " << key << ne; for (const auto& v : value) {cout << v << " ";} cout << endl;}}

//fast pow
ll ksm(ll a, ll b) {ll res = 1; while (b) {if (b & 1) {res = (res * a) % MOD;} a = (a * a) % MOD; b >>= 1;} return res;}

void solve() {

}

int main() {
    //ios::sync_with_stdio(0);
    //cin.tie(0), cout.tie(0);

    ll t = 1;
    rd(t);

    while (t--) {
        solve();
    }
    return 0;
}
