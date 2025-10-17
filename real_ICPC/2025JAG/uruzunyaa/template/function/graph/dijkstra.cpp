#include<bits/stdc++.h>
using namespace std;
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

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
vl dijkstra(vector<vector<pair<ll,ll>>> g,ll start){
	priority_queue<pair<ll,ll>> dj;
	vl cost(g.size(),inf);
	cost[start]=0;
	dj.push({start,0});
	while(!dj.empty()){
		ll nowcost=-dj.top().first;
		ll tmp=dj.top().second;
		dj.pop();
		if(cost[tmp]<nowcost)continue;
		rep(i,g[tmp].size()){
			if(cost[g[tmp][i].first]>nowcost+g[tmp][i].second){
				cost[g[tmp][i].first]=nowcost+g[tmp][i].second;
				dj.push({-cost[g[tmp][i].first],g[tmp][i].first});
			}
		}
	}
	return cost;
}

//使用例395-E
int main(){
	ll n,m,x;
	cin>>n>>m>>x;
	vector<vector<pair<ll,ll>>> g(n*2);
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back({v,1});
		g[n+v].push_back({n+u,1});
	}
	rep(i,n){
		g[i].push_back({n+i,x});
		g[n+i].push_back({i,x});
	}

	vl cost=dijkstra(g,0);
	cout<<min(cost[n-1],cost[n*2-1])<<endl;
	return 0;
}
