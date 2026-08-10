#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
//到達不可はinf
//pairの順序は{行き先,コスト}
vl dijkstra(vector<vector<pair<ll,ll>>> &g,ll start){
	priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> dj;
	vl cost(g.size(),inf);
	cost[start]=0;
	dj.push({0,start});
	while(!dj.empty()){
		ll nowcost=dj.top().first;
		ll tmp=dj.top().second;
		dj.pop();
		if(cost[tmp]<nowcost)continue;
		rep(i,g[tmp].size()){
			ll nxnode=g[tmp][i].first;
			ll nxcost=g[tmp][i].second;
			if(cost[nxnode]>nowcost+nxcost){
				cost[nxnode]=nowcost+nxcost;
				dj.push({cost[nxnode],nxnode});
			}
		}
	}
	return cost;
}

int main(){
	
	return 0;
}
