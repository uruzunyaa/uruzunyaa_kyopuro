#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll> 
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >= 0; --i)
constexpr ll INF = 9009009009009009009LL;


int main() {
    ll n;
	cin>>n;
	vl p(n);
	rep(i,n)cin>>p[i];

	//左からの累積GCDと右からの累積GCD
	vl left(n);
	ll gcds=0;
	rep(i,n){
		gcds=gcd(gcds,p[i]);
		left[i]=gcds;
	}
	vl right(n);
	gcds=0;
	rrep(i,n){
		gcds=gcd(gcds,p[i]);
		right[i]=gcds;
	}

	ll ans=0;
	rep(i,n-1){
		ans+=min(left[i],right[i]);
	}
	cout<<ans<<endl;
}