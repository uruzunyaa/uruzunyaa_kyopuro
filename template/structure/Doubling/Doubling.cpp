//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL


//functional_graphをダブリングする構造
struct Doubling {
	ll n;
	vvl dp;
	//functional_graphを与える
	Doubling(vl a) {
		n=a.size();
		dp.push_back(a);
		rep(i,60){
			vl nx(n);
			rep(j,n){
				nx[j]=dp.back()[dp.back()[j]];
			}
			dp.push_back(nx);
		}
	}
	
	// 頂点tからk回移動した時の頂点を返す(2^60を超える場合は注意)
	ll get(ll t, ll k){
		ll i=0;
		while (k > 0){
			if ((k&1) ==1)t=dp[i][t];
			i++;
			k >>= 1;
		}
		return t;
	}
};

//メイン
int main(){
	return 0;
}
