#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>
using namespace std;
using namespace atcoder;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl a(n);
	set<ll> s;
	vl nine(n+1,0);
	rep(i,n){
		cin>>a[i];
		nine[i+1]=nine[i];
		if(a[i]==9)nine[i+1]++;
		if(a[i]==1)s.insert(i+1);
	}
	while(q--){
		ll l,r;
		cin>>l>>r;
		ll ans=nine[r]-nine[l-1];
		for(const auto & val:s){
			if(l<=val&&val<=r)ans+=r-val;
		}
		cout<<ans<<endl;
	}
	return 0;
}
