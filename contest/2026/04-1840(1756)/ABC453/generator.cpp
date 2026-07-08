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
    
    uniform_int_distribution<ll> dist_N(2, 8);
    ll n = dist_N(rnd);
	
	//ここから先は問題固有
	uniform_int_distribution<ll> dist_lr(1,n-1);
    vector<pair<ll,ll>> lr(n);
    rep(i,n){
		lr[i].first=dist_lr(rnd);
		lr[i].second=dist_lr(rnd);
		if(lr[i].first>lr[i].second)swap(lr[i].first,lr[i].second);
	}

    cout << n <<"\n";
    rep(i,n) cout << lr[i].first << " "<< lr[i].second<<"\n";
    return 0;
}