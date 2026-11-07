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

//木の直系のパスの頂点リストを取得する。
//木の直系の長さは .size()-1 となる。
vl tree_diameter(vvl &g){
	ll n=g.size();
	
	//片方の端点を見つける
	vl tmpdist=bfs(g,0);
	ll a=0;
	rep(i,n){
		if(tmpdist[i]>tmpdist[a])a=i;
	}

	//相方の端点を見つける。
	vl dist=bfs(g,a);
	ll b=a;
	rep(i,n){
		if(dist[i]>dist[b])b=i;
	}

	//パスを復元
	vl ans;
	ans.push_back(b);
	while(ans.back()!=a){
		ll node=ans.back();
		for(auto val:g[node]){
			if(dist[node]-1==dist[val]){
				ans.push_back(val);
			}
		}
	}
	return ans;
}


//メイン
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro


vl c;
void dfs(vvl &g,ll mae,ll node,ll kyori,map<ll,ll> &mp){
	if(kyori==0){
		mp[c[node]]++;
		return;
	}
	for(auto val:g[node]){
		if(val==mae)continue;
		map<ll,ll> tmp;
		dfs(g,node,val,kyori-1,tmp);
		if(mp.size()<tmp.size())swap(mp,tmp);
		for(auto val:tmp){
			mp[val.first]+=val.second;
		}
	}
	return;
}

int main(){
	ll n;
	cin>>n;
	vvl g(n);
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	rep(i,n){
		ll cc;
		cin>>cc;
		c.push_back(cc);
	}
	vl dia=tree_diameter(g);

	vector<map<ll,ll>> mp;
	if(dia.size()%2==1){
		ll mid=dia[dia.size()/2];
		for(auto val:g[mid]){
			map<ll,ll> tmp;
			dfs(g,mid,val,(dia.size()-2)/2,tmp);
			mp.push_back(tmp);
		}
	}else{
		ll mid1=dia[dia.size()/2];
		ll mid2=dia[(dia.size()-2)/2];
		{
			map<ll,ll> tmp;
			dfs(g,mid1,mid2,(dia.size()-2)/2,tmp);
			mp.push_back(tmp);
		}
		{
			map<ll,ll> tmp;
			dfs(g,mid2,mid1,(dia.size()-2)/2,tmp);
			mp.push_back(tmp);
		}
	}

	map<ll,ll> allcnt;
	ll ans=0;
	rep(i,mp.size()){
		for(auto val:mp[i]){
			allcnt[val.first]+=val.second;
			ans-=val.second*val.second;
		}
	}

	for(auto val:allcnt){
		ans+=val.second*val.second;
	}

	cout<<ans/2<<endl;

	return 0;
}
