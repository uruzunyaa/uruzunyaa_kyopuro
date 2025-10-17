#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


ll n,m;
vector<vector<pair<ll,ll>>> g;
vl num;
bool dfs(ll node,ll xr,bool isfirst){
	if(num[node]!=-1){
		if(isfirst)return true;
		if(xr==num[node])return true;
		else return false;
	}
	num[node]=xr;
	rep(i,g[node].size()){
		if(!dfs(g[node][i].first,g[node][i].second^xr,false)){
			return false;
		}
	}
	return true;
}

//メイン
int main(){
	cin>>n>>m;
	g=vector<vector<pair<ll,ll>>>(n);
	num=vl(n,-1);
	rep(i,m){
		ll u,v,w;
		cin>>u>>v>>w,u--,v--;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	rep(i,n){
		if(!dfs(i,0,true)){
			cout<<-1<<endl;
			return 0;
		}
	}
	rep(i,n)if(num[i]==-1)num[i]=0;
	vdbg(num);

	return 0;
}
