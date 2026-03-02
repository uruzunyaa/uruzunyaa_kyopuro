//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#include <atcoder/convolution.hpp>

vvl g;

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
vl bfs(ll start){
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

//グラフgの頂点startからの最短経路を全ての頂点に対して求める。
vl many_bfs(deque<ll> start){
	queue<ll> bfs;
	vl dist(g.size(),inf);
	for(auto val:start){
		dist[val]=0;
		bfs.push(val);
	}
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

//u,vのパス成分を列挙。
deque<ll> paths;
bool get_path(ll b,ll u,ll v){
	if(u==v){
		paths.push_back(u);
		return true;
	}

	for(auto val:g[v]){
		if(val==b) continue;
		if(get_path(v,u,val)){
			paths.push_back(v);
			return true;
		}
	}
	return false;
}

//nodeからの距離を取得
vl dist4;
void dfs(ll mae,ll node,vl & ans,ll depth){
	if(depth==ans.size())ans.push_back(0);
	ans[depth]++;
	for(auto val:g[node]){
		if(val==mae)continue;
		dfs(node,val,ans,depth+1);
	}
	return;
}

//メイン
int main(){
	ll n;
	cin>>n;
	g=vvl(n);

	rep(i,n-1){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	//直径の両端を求める
	vl dist1=bfs(0);
	ll left=0;
	rep(i,n)if(dist1[i]>dist1[left])left=i;

	vl dist2=bfs(left);
	ll right=0;
	rep(i,n)if(dist2[i]>dist2[right])right=i;

	//直径のパスの中身を取得する
	get_path(-1,left,right);

	//スコアの最小値を計算
	vl dist3=many_bfs(paths);
	ll score=0;
	rep(i,n)score=max(score,dist3[i]);

	//必ず使うパスを求める
	rep(i,score)paths.pop_back(),paths.pop_front();

	//必ず使うパスからの距離を求める
	dist4 =many_bfs(paths);

	vl ans(n,0);
	if(paths.size()==1){
		vl tmp;
		dfs(-1,paths[0],tmp,0);
		vl cnv=atcoder::convolution_ll(tmp,tmp);
		rep(i,tmp.size())cnv[i*2]+=tmp[i];
		rep(i,cnv.size())ans[i]+=cnv[i]/2;

		for(auto val:g[paths[0]]){
			tmp.clear();
			dfs(paths[0],val,tmp,0);
			cnv=atcoder::convolution_ll(tmp,tmp);
			rep(i,tmp.size())cnv[i*2]+=tmp[i];
			rep(i,cnv.size())ans[i+2]-=cnv[i]/2;

		}
		
	}else{
		vl tmp;
		dfs(paths[1],paths[0],tmp,0);

		vl tmp2;
		dfs(paths[paths.size()-2],paths[paths.size()-1],tmp2,0);

		vl cnv=atcoder::convolution_ll(tmp,tmp2);
		rep(i,cnv.size())ans[i+paths.size()-1]+=cnv[i];
	}

	rep(i,n)cout<<ans[i]<<endl;
	return 0;
}
