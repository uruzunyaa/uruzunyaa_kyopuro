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

//Sを始点、#を壁、.が通路としてグリッドBFSをした結果を返す。
vvl grid_bfs(vector<string> s){
	ll h=s.size();
	ll w=s[0].size();
	vvl ans(h,vl(w,inf));
	queue<pair<ll,ll>> bfs;
	rep(i,h)rep(j,w)if(s[i][j]=='S')ans[i][j]=0,bfs.push({i,j});
	while(!bfs.empty()){
		auto[x,y]=bfs.front();
		bfs.pop();
		rep(d,4){
			ll nx=x+dx[d],ny=y+dy[d];
			if(nx<0||nx>=h||ny<0||ny>=w)continue;
			if(ans[nx][ny]!=inf||s[nx][ny]=='#')continue;
			ans[nx][ny]=ans[x][y]+1;
			bfs.push({nx,ny});
		}
	}
	return ans;
}


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
	ll n=9,m;
	cin>>m;
	vector<set<ll>> g(n);
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].insert(v);
		g[v].insert(u);
	}

	vl p(8);
	rep(i,8)cin>>p[i],p[i]--;

	map<vl,ll>dist;
	dist[p]=0;
	queue<vl> bfs;
	bfs.push(p);

	while(!bfs.empty()){
		vl tmp=bfs.front();
		bfs.pop();
		set<ll> akitmp;
		rep(i,9)akitmp.insert(i);
		rep(i,8)akitmp.erase(tmp[i]);
		ll aki=*akitmp.begin();
		rep(i,8){
			ll node=tmp[i];
			if(!g[aki].count(node))continue;
			vl next=tmp;
			next[i]=aki;
			if(dist.count(next))continue;
			dist[next]=dist[tmp]+1;
			bfs.push(next);
		}
		
	}
	vl ans;
	rep(i,8)ans.push_back(i);
	if(!dist.count(ans))cout<<-1<<endl;
	else cout<<dist[ans]<<endl;
	return 0;
}
