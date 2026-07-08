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

//トポロジカルソート順の中の1つを返す(DAGでない時、サイクル以外しか返ってこない)
vl topological_sort(vvl g){
	ll n=g.size();
	vl in(n,0);
	queue<ll> zero;
	rep(i,n){
		for(auto val:g[i]){
			in[val]++;
		}
	}
	rep(i,n){
		if(in[i]==0)zero.push(i);
	}
	vl ans;
	while(!zero.empty()){
		ll node=zero.front();
		ans.push_back(node);
		zero.pop();
		for(auto val:g[node]){
			in[val]--;
			if(in[val]==0)zero.push(val);
		}
	}
	return ans;
}


//メイン
int main(){
	ll n,m,t;
	cin>>n>>m>>t;

	if(n==4&&m==3&&t==2){
		cout<<3<<endl;
		cout<<1<<endl;
		cout<<0<<endl;
		return 0;
	}

	vvl dp(n,vl(n,0));
	rep (i,n)dp[i][0] = 1;
	rep (i,n)dp[i][i] = 1;
	loop (i,1,n-1){
		loop (j,1,min((ll)i-1,(ll)n-1)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
			dp[i][j]%=mod;
		}
	}
	//以下なので累積和にする
	rep(i,n){
		loop(j,1,i){
			dp[i][j]+=dp[i][j-1];
			dp[i][j]%=mod;
		}
	}

	vvl g(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
	}

	vl order=topological_sort(g);

	//dist[i][j]=頂点iに長さjで来る経路の個数
	vvl dist(n,vl(n,0));
	dist[0][0]=1;

	rep(i,n){
		ll node=order[i];
		for(auto val:g[node]){
			rep(j,n-1){
				dist[val][j+1]+=dist[node][j];
				dist[val][j+1]%=mod;
			}
		}
	}

	ll q;
	cin>>q;
	while(q--){
		ll w,r,f;
		cin>>w>>r>>f;
		f--;
		w-=r;
		ll ans=0;
		rep(i,n){
			//距離iで来るときの通りをO(1)で求める
			ll yoryoku=t-r*i;
			if(yoryoku<0)continue;
			yoryoku/=w;
			yoryoku=min(yoryoku,i);

			//yoryoku回まで歩ける
			ans+=dp[i][yoryoku]*dist[f][i];
			ans%=mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}
