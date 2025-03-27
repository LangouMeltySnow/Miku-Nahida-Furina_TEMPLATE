//Combination
class Comb{
    private:
    vector<ll> fac, invfac;
    public:
    Comb(ll n){
        fac.resize(n+1);
        invfac.resize(n+1);
        fac[0] = 1;
        for(ll i=1;i<=n;i++){
            fac[i] = (fac[i-1] * i)%MOD;
        }
        invfac[n] = ksm(fac[n], MOD-2);
        for(ll i=n-1;i>=0;i--){
            invfac[i] = (invfac[i+1] * (i+1))%MOD;
        }
    }
    ll C(ll n, ll m){
        if(n==0) return 1;
        if(n < m|| m < 0) return 0;
        return fac[n]*invfac[m]%MOD*invfac[n-m]%MOD;
    }
    ll A(ll n, ll m){
        if(n < m|| m < 0) return 0;
        return fac[n]*invfac[n-m]%MOD;
    }
};