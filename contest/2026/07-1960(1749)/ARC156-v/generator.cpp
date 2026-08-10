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
    
    uniform_int_distribution<ll> dist_N(1, 8);
    ll n = dist_N(rnd);
    uniform_int_distribution<ll> dist_K(1, 8);
    ll k = dist_K(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_a(0,10);
    vl a(n);
    rep(i,n){
        a[i]=dist_a(rnd);
	}

    cout << n << " "<<k<<"\n";
    rep(i,n) cout << a[i] << " ";
    cout<<"\n";
    return 0;
}