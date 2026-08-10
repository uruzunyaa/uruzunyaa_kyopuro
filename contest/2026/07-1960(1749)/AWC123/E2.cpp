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
#define inf 2000000000
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

// Union-Find
struct UnionFind {
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	// x を含むグループと y を含むグループとを併合する
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false; 
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};


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
bool vecin(vl a,ll x){
	rep(i,a.size()){
		if(a[i]==x)return true;
	}
	return false;
}

//メイン
int main(){
	ll n,m,k,t;
	cin>>n>>m>>k>>t;
	vector<vector<pair<ll,ll>>>g(n);
	rep(i,m){
		ll u,v,w;
		cin>>u>>v>>w;
		u--,v--;
		g[u].push_back({v,w});
	}
	vl s(k);
	vl p(k);
	vl z={0};
	vl orcost(n,0);
	rep(i,k){
		ll cnt;
		cin>>cnt;
		rep(j,cnt){
			ll ss;
			cin>>ss;
			ss--;
			if(!vecin(z,ss)){
				orcost[ss]=power(2,z.size());
				z.push_back(ss);
			}
			s[i]|=orcost[ss];
		}
		cin>>p[i];
	}


	vvl costmat(z.size(),vl(z.size()));
	rep(i,z.size()){
		vl tmp=dijkstra(g,z[i]);
		rep(j,z.size())costmat[i][j]=tmp[z[j]];
	}

	vvl dp(1LL<<z.size(),vl(z.size(),inf));
	dp[0][0]=0;
	rep(b,1LL<<z.size()){
		rep(i,z.size()){
			rep(j,z.size())dp[b|(1LL<<i)][i]=min(dp[b|(1LL<<i)][i],dp[b][j]+costmat[j][i]);
		}
		rep(i,z.size()){
			rep(j,z.size())dp[b|(1LL<<i)][i]=min(dp[b|(1LL<<i)][i],dp[b][j]+costmat[j][i]);
		}
	}



	ll ans=0;
	rep(b,(1LL<<z.size())){
		ll mn=inf;
		rep(i,z.size())mn=min(mn,dp[b][i]);
		if(mn>t)continue;
		ll scores=0;
		rep(i,k){
			if((b&s[i])==s[i])scores+=p[i];
		}
		ans=max(ans,scores);
	}
	cout<<ans<<endl;
	return 0;
}
