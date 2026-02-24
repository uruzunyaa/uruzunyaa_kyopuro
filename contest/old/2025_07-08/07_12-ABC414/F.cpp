//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


ll n,k;
vvl f;
vvl g;
queue<ll> qu;
void dfs(ll mae,ll node,ll dist,ll cost){
	//cout<<mae<<" "<<node<<" "<<dist<<" "<<cost<<endl;
	
	if(dist==k){
		if(f[node][0]==inf){
			f[node][0]=cost+1;
			qu.push(node);
		}
		return;
	}

	
	if(dist!=0&&(f[node][dist]==-inf||f[node][dist]==mae)){
		return;
	}
	
	bool f2=false;
	if(dist!=0&&f[node][dist]!=inf){
		f2=true;
	}

	if(dist!=0)f[node][dist]=mae;

	rep(i,g[node].size()){
		if(g[node][i]==mae)continue;
		dfs(node,g[node][i],dist+1,cost);
	}

	if(f2)f[node][dist]=-inf;
}

void solve(){
	cin>>n>>k;
	f=vvl(n,vl(k,inf));
	g=vvl(n);
	while(!qu.empty())qu.pop();
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	f[0][0]=0;
	qu.push(0);
	while(!qu.empty()){
		//cout<<qu.front()<<endl;
		dfs(-1,qu.front(),0,f[qu.front()][0]);
		qu.pop();
	}
	
	loop(i,1,n-1){
		if(f[i][0]!=inf)cout<<f[i][0]<<" ";
		else cout<<-1<<" ";
	}
	cout<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
