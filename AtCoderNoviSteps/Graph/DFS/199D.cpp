//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

void dfs(ll color,ll ind,vvl &g,vector<pair<ll,ll>> &list,vl &colors,ll &cnt){
	ll node=list[ind].first;
	colors[node]=color;
	for(auto val:g[node]){
		if(colors[node]==colors[val]){
			colors[node]=-1;
			return;
		}
	}
	if(ind==list.size()-1){
		cnt++;
		colors[node]=-1;
		return;
	}
	rep(i,3){
		if(colors[list[ind+1].second]==i)continue;
		dfs(i,ind+1,g,list,colors,cnt);
	}
	colors[node]=-1;
	return;
}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n);
	vector<bool> visited(n,false);

	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	ll ans=1;


	rep(i,n){
		if(visited[i])continue;
		queue<ll> bfs;
		bfs.push(i);
		visited[i]=true;
		vector<pair<ll,ll>> list;
		list.push_back({i,-1});
		
		while(!bfs.empty()){
			ll tmp=bfs.front();
			bfs.pop();
			for(auto val:g[tmp]){
				if(visited[val])continue;
				list.push_back({val,tmp});
				bfs.push(val);
				visited[val]=true;
			}
		}
		
		ll cnt=0;
		vl colors(n,-1);
		rep(i,3)dfs(i,0,g,list,colors,cnt);
		ans*=cnt;
	}
	cout<<ans<<endl;

	return 0;
}
