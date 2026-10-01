#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vout(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<"\n";
#define vpout(a) rep(ii,a.size()){cout<<a[ii].first<<" "<<a[ii].second<<"\n";};
#define vvout(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<"\n";}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<"\n";
#define inf 4000000000000000000LL
#define mod 998244353LL

//N頂点の単純無向グラフを生成する例。
int main(){
    random_device seed_gen;
    mt19937_64 mt(seed_gen());
    
    //頂点数
    uniform_int_distribution<ll> dist_N(1, 8);
    ll n = dist_N(mt);

    //完全グラフに対し辺を張る確率
	uniform_int_distribution<ll> dist_r(0,2);
    vector<pair<ll,ll>> g;
    rep(i,n)rep(j,i) {
		if(dist_r(mt))continue;
		g.push_back({j+1,i+1});
	}
    shuffle(g.begin(),g.end(),mt);

    cout << n << " "<< g.size()<<"\n";
    vpout(g);
    return 0;
}