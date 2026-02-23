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
	ll h,w;
	cin>>h>>w;
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	ll sx,sy;

	rep(i,h){
		rep(j,w){
			if(s[i][j]=='S')sx=i,sy=j;
		}
	}
	s[sx][sy]='#';
	rep(d,4){
		ll nx=sx+dx[d];
		ll ny=sy+dy[d];
		if(nx==-1||nx==h||ny==-1||ny==w)continue;
		if(s[nx][ny]=='#')continue;
		s[nx][ny]='S';
		vvl tmp = grid_bfs(s);
		rep(dd,4){
			ll px=sx+dx[dd];
			ll py=sy+dy[dd];
			if(px==-1||px==h||py==-1||py==w)continue;
			if(px==nx&&py==ny)continue;
			if(tmp[px][py]!=inf){
				cout<<"Yes"<<endl;
				return 0;
			}
		}
		s[nx][ny]='.';
	}
	cout<<"No"<<endl;
	return 0;
}
