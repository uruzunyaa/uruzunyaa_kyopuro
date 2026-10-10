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

int main(){
	ll h,w;
	cin>>h>>w;
	vector<string> s(h);
	rep(i,h){
		rep(j,w){
			ll a;
			cin>>a;
			if(a==1)s[i].push_back('#');
			else s[i].push_back('.');
		}
	}
	vector<vvl> ans(h,vvl(w,vl(2,inf)));
	queue<vl> bfs;
	ans[0][0][0]=0;
	bfs.push({0,0,0});
	ans[0][0][1]=0;
	bfs.push({0,0,1});
	while(!bfs.empty()){
		vl now=bfs.front();
		bfs.pop();
		rep(dd,2){
			ll d=dd*2+now[2];
			ll nx=now[0]+dx[d],ny=now[1]+dy[d];
			ll nz=1-now[2];
			if(nx<0||nx>=h||ny<0||ny>=w)continue;
			if(ans[nx][ny][nz]!=inf||s[nx][ny]=='#')continue;
			ans[nx][ny][nz]=ans[now[0]][now[1]][now[2]]+1;
			bfs.push({nx,ny,nz});
		}
	}

	// rep(i,h){
	// 	rep(j,w){
	// 		cout<<"{"<<ans[i][j][0]<<","<<ans[i][j][1]<<"},";
	// 	}
	// 	cout<<endl;
	// }

	ll num=min(ans.back().back()[0],ans.back().back()[1]);

	if(num==inf){
		cout<<"NONE"<<endl;
	}else{
		cout<<num<<endl;
	}
	return 0;
}
