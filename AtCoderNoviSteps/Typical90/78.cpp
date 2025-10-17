#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		if(a>b)swap(a,b);
		a--,b--;

		g[b].push_back(a);
	}

	ll ans=0;
	rep(i,n)if(g[i].size()==1)ans++;
	cout<<ans<<endl;
	return 0;
}
