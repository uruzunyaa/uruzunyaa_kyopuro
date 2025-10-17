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


/*
void range_chmin(int l, int r, ll x) {Xでchmin}
void range_chmax(int l, int r, ll x) {Xでchmax}
void range_add(int l, int r, ll x) {Xを区間加算}
void range_update(int l, int r, ll x) {Xで区間変更}
ll range_min(int l, int r) {区間最小値を取得}
ll range_max(int l, int r) {区間最大値を取得}
ll range_sum(int l, int r) {区間和を取得}
*/

struct AngelBeats {
  using i64 = long long;
  static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

  struct alignas(32) Node {
    i64 sum = 0, g1 = 0, l1 = 0;
    i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
  };

  vector<Node> v;
  i64 n, log;

  AngelBeats() {}
  AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
  AngelBeats(const vector<i64>& vc) {
    n = 1, log = 0;
    while (n < (int)vc.size()) n <<= 1, log++;
    v.resize(2 * n);
    for (i64 i = 0; i < (int)vc.size(); ++i) {
      v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i];
    }
    for (i64 i = n - 1; i; --i) update(i);
  }

  void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
  void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
  void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
  void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
  i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
  i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
  i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

 private:
  void update(int k) {
    Node& p = v[k];
    Node& l = v[k * 2 + 0];
    Node& r = v[k * 2 + 1];

    p.sum = l.sum + r.sum;

    if (l.g1 == r.g1) {
      p.g1 = l.g1;
      p.g2 = max(l.g2, r.g2);
      p.gc = l.gc + r.gc;
    } else {
      bool f = l.g1 > r.g1;
      p.g1 = f ? l.g1 : r.g1;
      p.gc = f ? l.gc : r.gc;
      p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
    }

    if (l.l1 == r.l1) {
      p.l1 = l.l1;
      p.l2 = min(l.l2, r.l2);
      p.lc = l.lc + r.lc;
    } else {
      bool f = l.l1 < r.l1;
      p.l1 = f ? l.l1 : r.l1;
      p.lc = f ? l.lc : r.lc;
      p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
    }
  }

  void push_add(int k, i64 x) {
    Node& p = v[k];
    p.sum += x << (log + __builtin_clz(k) - 31);
    p.g1 += x;
    p.l1 += x;
    if (p.g2 != -INF) p.g2 += x;
    if (p.l2 != INF) p.l2 += x;
    p.add += x;
  }
  void push_min(int k, i64 x) {
    Node& p = v[k];
    p.sum += (x - p.g1) * p.gc;
    if (p.l1 == p.g1) p.l1 = x;
    if (p.l2 == p.g1) p.l2 = x;
    p.g1 = x;
  }
  void push_max(int k, i64 x) {
    Node& p = v[k];
    p.sum += (x - p.l1) * p.lc;
    if (p.g1 == p.l1) p.g1 = x;
    if (p.g2 == p.l1) p.g2 = x;
    p.l1 = x;
  }
  void push(int k) {
    Node& p = v[k];
    if (p.add != 0) {
      push_add(k * 2 + 0, p.add);
      push_add(k * 2 + 1, p.add);
      p.add = 0;
    }
    if (p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
    if (p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

    if (p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
    if (p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
  }

  void subtree_chmin(int k, i64 x) {
    if (v[k].g1 <= x) return;
    if (v[k].g2 < x) {
      push_min(k, x);
      return;
    }
    push(k);
    subtree_chmin(k * 2 + 0, x);
    subtree_chmin(k * 2 + 1, x);
    update(k);
  }

  void subtree_chmax(int k, i64 x) {
    if (x <= v[k].l1) return;
    if (x < v[k].l2) {
      push_max(k, x);
      return;
    }
    push(k);
    subtree_chmax(k * 2 + 0, x);
    subtree_chmax(k * 2 + 1, x);
    update(k);
  }

  template <int cmd>
  inline void _apply(int k, i64 x) {
    if constexpr (cmd == 1) subtree_chmin(k, x);
    if constexpr (cmd == 2) subtree_chmax(k, x);
    if constexpr (cmd == 3) push_add(k, x);
    if constexpr (cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
  }

  template <int cmd>
  void inner_apply(int l, int r, i64 x) {
    if (l == r) return;
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) _apply<cmd>(l++, x);
        if (r & 1) _apply<cmd>(--r, x);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <int cmd>
  inline i64 e() {
    if constexpr (cmd == 1) return INF;
    if constexpr (cmd == 2) return -INF;
    return 0;
  }

  template <int cmd>
  inline void op(i64& a, const Node& b) {
    if constexpr (cmd == 1) a = min(a, b.l1);
    if constexpr (cmd == 2) a = max(a, b.g1);
    if constexpr (cmd == 3) a += b.sum;
  }

  template <int cmd>
  i64 inner_fold(int l, int r) {
    if (l == r) return e<cmd>();
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    i64 lx = e<cmd>(), rx = e<cmd>();
    while (l < r) {
      if (l & 1) op<cmd>(lx, v[l++]);
      if (r & 1) op<cmd>(rx, v[--r]);
      l >>= 1;
      r >>= 1;
    }
    if constexpr (cmd == 1) lx = min(lx, rx);
    if constexpr (cmd == 2) lx = max(lx, rx);
    if constexpr (cmd == 3) lx += rx;
    return lx;
  }
};



//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	AngelBeats bt(a);
	ll q;
	cin>>q;
	while(q--){
		ll l,r,x;
		cin>>l>>r>>x;
		l--;
		ll ans=bt.range_sum(l,r);
		bt.range_add(l,r,-x);
		bt.range_chmax(l,r,0);
		ans-=bt.range_sum(l,r);
		cout<<ans<<endl;
	}
	return 0;
}
