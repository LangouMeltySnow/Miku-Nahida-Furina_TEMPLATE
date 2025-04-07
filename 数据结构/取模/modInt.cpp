template<class T>
constexpr T power(T a, ull b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template<unsigned P>
constexpr unsigned mulMod(unsigned a, unsigned b) {
    return ull(a) * b % P;
}

template<ull P>
constexpr ull mulMod(ull a, ull b) {
    ull res = a * b - ull(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr ll safeMod(ll x, ll m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr pair<ll, ll> invGcd(ll a, ll b) {
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }

    ll s = b, t = a;
    ll m0 = 0, m1 = 1;

    while (t) {
        ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        swap(s, t);
        swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

template<unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    template<unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_ % mod()) {}
    template<signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = make_signed_t<U>;
        S v = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static U mod() {
        return P;
    }

    constexpr U val() const {
        return x;
    }

    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const {
        return power(*this, mod() - 2);
    }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr istream &operator>>(istream &is, ModIntBase &a) {
        ll i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const ModIntBase &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr strong_ordering operator<= > (const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() <= > rhs.val();
    }

private:
    U x;
};

template<unsigned P>
using ModInt = ModIntBase<unsigned, P>;
template<ull P>
using ModInt64 = ModIntBase<ull, P>;

struct Barrett {
public:
    Barrett(unsigned m_) : m(m_), im((ull)(-1) / m_ + 1) {}

    constexpr unsigned mod() const {
        return m;
    }

    constexpr unsigned mul(unsigned a, unsigned b) const {
        ull z = a;
        z *= b;

        ull x = ull((u128(z) * im) >> 64);

        unsigned v = unsigned(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    unsigned m;
    ull im;
};

template<unsigned Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template<unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_ % mod()) {}
    template<signed_integral T>
    constexpr DynModInt(T x_) {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(unsigned m) {
        bt = m;
    }

    static unsigned mod() {
        return bt.mod();
    }

    constexpr unsigned val() const {
        return x;
    }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt &operator*=(const DynModInt &rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt &operator+=(const DynModInt &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt &operator-=(const DynModInt &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt &operator/=(const DynModInt &rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs) {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr istream &operator>>(istream &is, DynModInt &a) {
        ll i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const DynModInt &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr strong_ordering operator<= > (const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() <= > rhs.val();
    }

private:
    unsigned x;
    static Barrett bt;
};

template<unsigned Id>
Barrett DynModInt<Id>::bt = 998244353;