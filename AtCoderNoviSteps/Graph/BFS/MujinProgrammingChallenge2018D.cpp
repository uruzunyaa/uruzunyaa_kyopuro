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

ll rev(ll x){
	string s=to_string(x);
	reverse(s.begin(),s.end());
	return stoll(s);
}

vl g(1e6);
vl cost(1e6,inf);
bool dfs(ll node){
	if(cost[node]==1)return true;
	if(cost[node]==0)return false;
	cost[node]=1;
	if(dfs(g[node])){
		return true;
	}else{
		cost[node]=0;
		return false;
	}
}
int main(){
	rep(i,1e6){
		ll x=i/1000;
		ll y=i%1000;
		if(x<y)x=rev(x);
		else y=rev(y);
		if(x<y)y=y-x;
		else x=x-y;
		g[i]=x*1000+y;
	}
	
	rep(i,1000){
		cost[i]=0;
		cost[i*1000]=0;
	}
	rep(i,1e6)dfs(i);


	ll n,m;
	cin>>n>>m;

	ll ans=0;
	loop(i,1,n)loop(j,1,m){
		ans+=cost[i*1000+j];
	}
	cout<<ans<<endl;
	return 0;
}
