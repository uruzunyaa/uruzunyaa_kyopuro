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
vl bfs(vvl &g,ll start){
	queue<ll> bfs;
	vl dist(g.size(),inf);
	dist[start]=0;
	bfs.push(start);
	while(!bfs.empty()){
		ll tmp=bfs.front();
		bfs.pop();
		rep(i,g[tmp].size()){
			ll next=g[tmp][i];
			if(dist[next]!=inf)continue;
			dist[next]=dist[tmp]+1;
			bfs.push(next);
		}
	}
	return dist;
}

int main(){
	
	return 0;
}
