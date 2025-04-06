```cpp
#include <bits/stdc++.h>
using namespace std;

#define pb push_back 
#define eb emplace_back 
#define fi first
#define se second
#define ne " -> "

typedef long long ll;
typedef pair<long long,long long> PLL;
typedef tuple<ll,ll,ll> TLLL;
//const ll inf =  0x3f3f3f3f;
const ll INF = INT_MAX;
const ll MOD = 1000000007;
//const ll MOD = 998244353;

//print functions
inline ll read(){ll x=0;short f=1;char c=getchar();while((c<'0'||c>'9')&&c!='-') c=getchar();if(c=='-') f=-1,c=getchar();while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();x*=f;return x;}  
inline void pt(ll x){if(x<0) putchar('-'),x=-x;if(x>9) pt(x/10);putchar(x%10+'0');}
inline void print(ll x){pt(x), puts("");}
inline void printVec(vector<ll> &vec){for(const auto t:vec)pt(t),putchar(' ');puts("");}
inline void printMap(const map<ll, ll>& g) {for(const auto& [key, value]:g){cout<<"key: "<<key<<ne<<value<<" ";}puts("");}


struct Data{
    ll val;
};

struct Node
{
    ll l, r;
    ll data;
};

class SegmentTree{
    private:
    vector<Node> tree;
    vector<ll> tag;

    ll ls(ll p){
        return p<<1;
    }

    ll rs(ll p){
        return p<<1|1;
    }

    void push_up(ll p){
        tree[p].data = tree[ls(p)].data + tree[rs(p)].data;
    }

    void build(vector<ll> & arr, ll p, ll l, ll r){
        tree[p].l = l;
        tree[p].r = r;
        tag[p] = 0;
        if (l == r){
            tree[p].data = arr[l];
            return;
        }
        ll mid = (l + r)>>1;
        build(arr, ls(p), l, mid);
        build(arr, rs(p), mid+1, r);
        push_up(p);
    }

    void push_tag(ll p, ll d){
        tag[p] += d;
        tree[p].data += (tree[p].r - tree[p].l + 1) * d;
    }

    void push_down(ll p){
        if(tag[p]){
            ll mid = (tree[p].l + tree[p].r)>>1;
            push_tag(ls(p), tag[p]);
            push_tag(rs(p), tag[p]);
            tag[p] = 0;
        }
    }

    void push_change_tag(ll p, ll d){
        tag[p] = d;
        tree[p].data = (tree[p].r - tree[p].l + 1) * d;
    }
    
    void push_change_down(ll p){
        if(tag[p]){
            ll mid = (tree[p].l + tree[p].r)>>1;
            push_change_tag(ls(p), tag[p]);
            push_change_tag(rs(p), tag[p]);
            tag[p] = 0;
        }
    }

    void update(ll L, ll R, ll p, ll d){
        if(L<=tree[p].l&&tree[p].r<=R){
            push_tag(p, d);
            return ;
        }
        push_down(p);
        ll mid = (tree[p].l+tree[p].r)>>1;
        if (L <= mid) update(L, R, ls(p), d);
        if (R > mid) update(L, R, rs(p), d);
        push_up(p);
    }

    void change(ll L, ll R, ll p, ll d){
        if(L<=tree[p].l&&tree[p].r<=R){
            push_change_tag(p, d);
            return ;
        }
        push_change_down(p);
        ll mid = (tree[p].l+tree[p].r)>>1;
        if (L <= mid) change(L, R, ls(p), d);
        if (R > mid) change(L, R, rs(p), d);
        push_up(p);
    }

    ll query(ll L, ll R, ll p){
        if (L<=tree[p].l&&tree[p].r<=R){
            return tree[p].data;
        }
        push_down(p);
        ll mid = (tree[p].l + tree[p].r)>>1;
        ll res = 0;
        if (L <= mid) res += query(L, R, ls(p));
        if (R > mid) res += query(L, R, rs(p));
        return res;
    }

    public:
    SegmentTree(vector<ll> & arr){
        ll n = arr.size()-1;
        // arr 1-base idx;
        tree.resize(4*n);
        tag.resize(4*n);
        build(arr, 1, 1, n);
    }

    void update(ll l, ll r, ll d){
        update(l, r, 1, d);
    }

    void change(ll l, ll r, ll d){
        change(l, r, 1, d);
    }
    
    ll query(ll l, ll r){
        return query(l, r, 1);
    }
};

signed main(){
    ll n = read(), m = read();
    vector<ll> a(n+1);
    for(ll i=1;i<=n;i++){
        a[i] = read();
    }
    SegmentTree seg(a);
    ll q, L, R, d;
    while(m--){
        ll q = read();
        if(q==1){
            L = read(), R = read(), d = read();
            seg.update(L, R, d);
        }
        else{
            L = read(), R = read();
            print(seg.query(L, R));
        }
    }
}
```

