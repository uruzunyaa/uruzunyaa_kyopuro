#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//N頂点のグラフを生成する例。
int main(){
    random_device seed_gen;
    mt19937_64 rnd(seed_gen());
    
    uniform_int_distribution<ll> dist_N(6, 10);
    ll n = dist_N(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_k(1,n);
	uniform_int_distribution<ll> dist_a(1,100);

	vl k(n),a(n);

	rep(i,n){
		k[i]=dist_k(rnd);
		a[i]=dist_a(rnd);
	}


    cout << n <<"\n";
    rep(i,n) cout << k[i] << " "<< a[i]<<"\n";
    return 0;
}