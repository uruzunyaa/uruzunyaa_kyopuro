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

//メイン
int main(){
	ll n,m,k,x;
	cin>>n>>m>>k>>x;
	x--;
	vl a(n);
	vector<pair<ll,ll>> cost(n,{inf,-2});
	rep(i,n)cin>>a[i];
	priority_queue<pair<ll,ll>> pq;
	rep(i,k){
		ll s;
		cin>>s;
		s--;
		
		pq.push({-a[s],s});
		cost[s]={a[s],-1};
	}

	vvl g(n);
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
	}


	while(!pq.empty()){
		ll check=-pq.top().first;
		ll tmp=pq.top().second;
		pq.pop();
		if(check>cost[tmp].first)continue;
		rep(i,g[tmp].size()){
			if(cost[g[tmp][i]].first>=cost[tmp].first+a[g[tmp][i]]){
				cost[g[tmp][i]]={cost[tmp].first+a[g[tmp][i]],tmp};
				pq.push({-cost[g[tmp][i]].first,g[tmp][i]});
			}
		}
	}
	if(cost[x].second==-2){
		cout<<-1<<endl;
		return 0;
	}
	vl ans;
	ans.push_back(x);
	while(cost[x].second!=-1){
		x=cost[x].second;
		ans.push_back(x);
	}
	reverse(ans.begin(),ans.end());
	rep(i,ans.size())ans[i]++;

	cout<<ans.size()<<endl;
	vdbg(ans);
	return 0;
}
