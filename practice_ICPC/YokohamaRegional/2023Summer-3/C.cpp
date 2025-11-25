#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
const ll mod = 998244353;
const ll INF = 1LL << 60;

ll power_mod(ll n, ll k){
    ll result = 1;
    while (k > 0){
        if ((k & 1) == 1) result = (result * n) % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return result;
}

vector<ll> fact = {1};
vector<ll> factinv = {1};

ll ncrmd(ll n, ll r){
    while(fact.size() <= n){
        ll i = fact.size();
        fact.push_back((fact[i - 1] * i) % mod);
        factinv.push_back(power_mod(fact[i], mod - 2));
    }
    ll ans = fact[n];
    ans *= factinv[r];
    ans %= mod;
    ans *= factinv[n - r];
    ans %= mod;
    return ans;
}

int main() {
	ll m;
	cin>>m;
	loop(n,1,m){
		//ある数に関する過半数
		ll tmp=power_mod(2,n*2);
		tmp+=mod-ncrmd(n*2,n);
		tmp%=mod;
		tmp*=power_mod(2,mod-2);
		tmp%=mod;

		tmp*=

		//過半数m種類
		tmp*=m;
		tmp%=mod;

		ll ans=power_mod(m,2*n);
		ans+=mod-tmp;
		ans%=mod;
		cout<<ans<<endl;
	}
    return 0;
}