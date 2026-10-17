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

// 分子と分母が INF 以下である非負の既約分数のうち次のものを返す
// first : f(x) が false である最大の既約分数 x
// second : f(x) が true である最小の既約分数 x
// ただし
// - f(0) = true の場合は (0/1, 0/1) を返す
// - true になる分数が存在しない場合は (?, 1/0) を返す
// - INF = 0 の場合は (0/1, 1/0) を返す
template <typename I>
pair<pair<I, I>, pair<I, I>> binary_search_on_stern_brocot_tree(
    function<bool(pair<I, I>)> f, const I &INF) {
  // INF >= 0
  assert(0 <= INF);
  SternBrocotTreeNode<I> m;
  if (INF == 0) return {m.lower_bound(), m.upper_bound()};

  // INF 条件を超える or f(m) = return_value である
  auto over = [&](bool return_value) {
    return max(m.x, m.y) > INF or f(m.get()) == return_value;
  };

  if (f(make_pair(0, 1))) return {m.lower_bound(), m.lower_bound()};
  int go_left = over(true);
  for (; true; go_left ^= 1) {
    if (go_left) {
      // f(M) = true -> (L, M] に答えがある
      // (f(L * b + M) = false) or (INF 超え) になる b の最小は？
      I a = 1;
      for (; true; a *= 2) {
        m.go_left(a);
        if (over(false)) {
          m.go_parent(a);
          break;
        }
      }
      for (a /= 2; a != 0; a /= 2) {
        m.go_left(a);
        if (over(false)) m.go_parent(a);
      }
      m.go_left(1);
      if (max(m.get().first, m.get().second) > INF)
        return {m.lower_bound(), m.upper_bound()};
    } else {
      // f(M) = false -> (M, R] に答えがある
      // (f(M + R * b) = true) or (INF 超え) になる b の最小は？
      I a = 1;
      for (; true; a *= 2) {
        m.go_right(a);
        if (over(true)) {
          m.go_parent(a);
          break;
        }
      }
      for (a /= 2; a != 0; a /= 2) {
        m.go_right(a);
        if (over(true)) m.go_parent(a);
      }
      m.go_right(1);
      if (max(m.get().first, m.get().second) > INF)
        return {m.lower_bound(), m.upper_bound()};
    }
  }
}

//メイン
int main(){
	// 分子と分母が INF 以下である非負の既約分数のうち次のものを返す
	// first : f(x) が false である最大の既約分数 x
	// second : f(x) が true である最小の既約分数 x
	// ただし
	// - f(0) = true の場合は (0/1, 0/1) を返す
	// - true になる分数が存在しない場合は (?, 1/0) を返す
	// - INF = 0 の場合は (0/1, 1/0) を返す
	return 0;
}
