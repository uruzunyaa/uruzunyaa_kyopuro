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


//xor基底を求める、確認する。
struct XorBasis {
	//基底のリスト
    vl basis;

	//xを追加
    void add(ll x) {
        for (auto b : basis) {
            x=min(x,x^b);
        }
        if (x != 0) {
            basis.push_back(x);
		}
    }

    //xが含まれているか確認
	ll check(ll x){
       	for (auto b : basis) {
            x=min(x,x^b);
    	}
        return x;
    }
};

#line 1 "math/fft/fast-walsh-hadamard-transform.hpp"
/**
 * @brief Fast Walsh Hadamard Transform (高速ウォルシュアダマール変換)
 */
template <typename T>
void fast_walsh_hadamard_transform(vector<T>& f, bool inv = false) {
  const int n = (int)f.size();
  assert((n & (n - 1)) == 0);
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i << 1) {
      for (int k = 0; k < i; k++) {
        T s = f[j + k], t = f[j + k + i];
        f[j + k] = s + t;
        f[j + k + i] = s - t;
      }
    }
  }
  if (inv) {
    T inv_n = T(1) / n;
    for (auto& x : f) x *= inv_n;
  }
}
#line 2 "math/fft/bitwise-xor-convolution.hpp"

/**
 * @brief Bitwise Xor Convolution (Bitwise-XOR畳み込み)
 */
template <typename T>
vector<T> bitwise_xor_convolution(vector<T> f, vector<T> g) {
  const int n = (int)f.size();
  assert(f.size() == g.size());
  assert((n & (n - 1)) == 0);
  fast_walsh_hadamard_transform(f, false);
  fast_walsh_hadamard_transform(g, false);
  for (int i = 0; i < n; i++) f[i] *= g[i];
  fast_walsh_hadamard_transform(f, true);
  return f;
}


XorBasis xb;
vl dist;
vector<vector<pair<ll,ll>>> g;
void dfs(ll mae,ll node,ll cost){
	if(dist[node]!=-1){
		xb.add(cost^dist[node]);
		return;
	}
	dist[node]=cost;
	for(auto val:g[node]){
		if(mae==val.first)continue;
		dfs(node,val.first,cost^val.second);
	}
}

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	xb=XorBasis();
	dist=vl(n,-1);
	g=vector<vector<pair<ll,ll>>>();

	rep(i,m){
		ll u,v,w;
		cin>>u>>v>>w;
		u--,v--;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}

	dfs(-1,0,0);

	rep(i,n){
		dist[i]=xb.check(dist[i]);
	}

	
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
