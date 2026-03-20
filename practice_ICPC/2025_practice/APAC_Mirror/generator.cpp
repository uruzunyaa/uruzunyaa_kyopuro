#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000

int main(){
    random_device seed_gen;
	mt19937_64 rnd(seed_gen());

	uniform_int_distribution<ll> dist_N(2,10);
	ll n= dist_N(rnd);

	vl a;
	loop(i,1,n-1){
		uniform_int_distribution<ll> dist_A(1,i);
		a.push_back(dist_A(rnd));
	}

	cout<<n<<"\n";
	rep(i,n-1)cout<<a[i]<<" ";
	cout<<"\n";
}