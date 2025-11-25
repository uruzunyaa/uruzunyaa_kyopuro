#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
const ll mod = 998244353;
const ll INF = 1LL << 60;

int main() {
	ll n;
	cin>>n;
	loop(i,1,30){
		cout<<i<<" ";
		ll ans=n*i;
		ans%=mod;
		cout<<ans<<endl;
	}
    return 0;
}