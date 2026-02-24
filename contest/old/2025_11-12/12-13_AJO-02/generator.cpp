#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>


int main(){
    random_device seed_gen;
    mt19937_64 rnd(seed_gen());
    
    uniform_int_distribution<ll> dist_N(8, 12);
    ll n = dist_N(rnd);
	uniform_int_distribution<ll> dist_K(1, n);
	ll k = dist_K(rnd);

	cout<<n<<"\n";
    loop(i,1,n)cout << n << " "<< i <<"\n";
    return 0;
}