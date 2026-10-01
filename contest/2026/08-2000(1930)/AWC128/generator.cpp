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
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_r(0,2);
    vector<pair<ll,ll>> g;
    rep(i,n)rep(j,i) {
		if(dist_r(rnd))continue;
		g.push_back({j+1,i+1});
	}

	cout<<1<<"\n";
    cout << n << " "<< g.size()<<"\n";
    rep(i,g.size()) cout << g[i].first << " "<< g[i].second<<"\n";
    return 0;
}