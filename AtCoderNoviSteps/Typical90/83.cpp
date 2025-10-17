#include<bits/stdc++.h>
using namespace std;
#define ll int
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
	vector<unordered_set<ll>> g(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].insert(b);
		g[b].insert(a);
	}

	vector<pair<ll,ll>> color(n,{-1,1});

	map<ll,pair<ll,ll>> log;
	//log[頂点番号]={時刻,色}

	ll q;
	cin>>q;

	rep(i,q){
		ll x,y;
		cin>>x>>y;
		x--;
		
		for(const auto & val:log){
			if(g[x].count(val.first)){
				color[x]=max(color[x],val.second);
			}
		}
		cout<<color[x].second<<endl;
		color[x]={i,y};

		if(g[x].size()*g[x].size()<=m){
			for(const auto & val:g[x]){
				color[val]={i,y};
			}
		}else{
			log[x]={i,y};
		}
	}
	return 0;
}
