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
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
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
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
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
//{行き先,コスト}
vl dijkstra(vector<vector<pair<ll,ll>>> g,ll start){
	priority_queue<pair<ll,ll>> dj;
	vl cost(g.size(),inf);
	cost[start]=0;
	dj.push({0,start});
	while(!dj.empty()){
		ll nowcost=-dj.top().first;
		ll tmp=dj.top().second;
		dj.pop();
		if(cost[tmp]<nowcost)continue;
		rep(i,g[tmp].size()){
			if(cost[g[tmp][i].first]>nowcost+g[tmp][i].second){
				cost[g[tmp][i].first]=nowcost+g[tmp][i].second;
				dj.push({-cost[g[tmp][i].first],g[tmp][i].first});
			}
		}
	}
	return cost;
}

void solve(){
	ll h,w;
	cin>>h>>w;
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	vector<vector<pair<ll,ll>>> g(h*w*4);
	rep(x,h)rep(y,w){
		rep(d,4){
			ll nx=x+dx[d];
			ll ny=y+dy[d];
			if(nx<0||nx>=h||ny<0||ny>=w)continue;

			ll nind=4*(w*nx+ny)+d;

			//下
			if(d==0){
				ll now=4*(w*x+y);
				if(s[x][y]=='A'){
					g[now].push_back({nind,0});
					g[now+1].push_back({nind,1});
					g[now+3].push_back({nind,1});
				}
				if(s[x][y]=='B'){
					g[now].push_back({nind,1});
					g[now+1].push_back({nind,0});
					g[now+3].push_back({nind,1});
				}
				if(s[x][y]=='C'){
					g[now].push_back({nind,1});
					g[now+1].push_back({nind,1});
					g[now+3].push_back({nind,0});
				}
			}
			//右
			if(d==1){
				ll now=4*(w*x+y);
				if(s[x][y]=='A'){
					g[now+1].push_back({nind,0});
					g[now].push_back({nind,1});
					g[now+2].push_back({nind,1});
				}
				if(s[x][y]=='B'){
					g[now+1].push_back({nind,1});
					g[now].push_back({nind,0});
					g[now+2].push_back({nind,1});
				}
				if(s[x][y]=='C'){
					g[now+1].push_back({nind,1});
					g[now].push_back({nind,1});
					g[now+2].push_back({nind,0});
				}
			}
			if(d==2){
				ll now=4*(w*x+y);
				if(s[x][y]=='A'){
					g[now+2].push_back({nind,0});
					g[now+1].push_back({nind,1});
					g[now+3].push_back({nind,1});
				}
				if(s[x][y]=='B'){
					g[now+2].push_back({nind,1});
					g[now+1].push_back({nind,1});
					g[now+3].push_back({nind,0});
				}
				if(s[x][y]=='C'){
					g[now+2].push_back({nind,1});
					g[now+1].push_back({nind,0});
					g[now+3].push_back({nind,1});
				}
			}
			if(d==3){
				ll now=4*(w*x+y);
				if(s[x][y]=='A'){
					g[now+3].push_back({nind,0});
					g[now].push_back({nind,1});
					g[now+2].push_back({nind,1});
				}
				if(s[x][y]=='B'){
					g[now+3].push_back({nind,1});
					g[now].push_back({nind,1});
					g[now+2].push_back({nind,0});
				}
				if(s[x][y]=='C'){
					g[now+3].push_back({nind,1});
					g[now].push_back({nind,0});
					g[now+2].push_back({nind,1});
				}
			}
		}
	}
	vl tmp=dijkstra(g,1);

	ll ans=inf;
	ans=min(ans,tmp[h*w*4-3]+1);
	if(s[h-1][w-1]=='A'){
		ans=min(ans,tmp[h*w*4-3]);
	}
	ans=min(ans,tmp[h*w*4-4]+1);
	if(s[h-1][w-1]=='B'){
		ans=min(ans,tmp[h*w*4-4]);
	}
	
	cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
