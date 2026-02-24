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

template <typename Node>
struct Beats {
  int n, log;
  vector<Node> v;

  template <typename T>
  Beats(vector<T>& vc) {
    n = 1, log = 0;
    while (n < (int)vc.size()) n <<= 1, log++;
    v.resize(2 * n);
    for (int i = 0; i < (int)vc.size(); ++i) v[i + n] = Node(vc[i]);
    for (int i = n - 1; i; --i) _update(i);
  }

  template <typename T>
  void apply(int l, int r, T x) {
    if (l == r) return;
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1) _apply(l++, x);
        if (r & 1) _apply(--r, x);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }
    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l) _update(l >> i);
      if (((r >> i) << i) != r) _update((r - 1) >> i);
    }
  }

  template <typename F>
  void query(int l, int r, const F& f) {
    if (l == r) return;
    l += n, r += n;
    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l) _push(l >> i);
      if (((r >> i) << i) != r) _push((r - 1) >> i);
    }
    while (l < r) {
      if (l & 1) f(v[l++]);
      if (r & 1) f(v[--r]);
      l >>= 1;
      r >>= 1;
    }
  }

 private:
  void _push(int i) { v[i].push(v[2 * i + 0], v[2 * i + 1]); }
  void _update(int i) { v[i].update(v[2 * i + 0], v[2 * i + 1]); }
  template <typename T>
  void _apply(int i, T x) {
    bool res = v[i].apply(x);
    if (i < n && res == false) {
      _push(i);
      _apply(i * 2 + 0, x);
      _apply(i * 2 + 1, x);
      _update(i);
    }
  }
};

struct Node {
  ll mx = 0;
  bool f = true;

  Node() {}
  Node(ll t) : mx(t) {}

  void update(Node& l, Node& r) {
    mx = l.mx + r.mx;
	
  }
  
  void push(Node& l, Node& r) {
    if (laz1 != 0) {
      l.add(laz1);
      r.add(laz1);
      laz1 = 0;
    }
    if (md) {
      l.getmod();
      r.getmod();
      md = false;
    }
    if (laz2 != 0) {
      l.add(laz2);
      r.add(laz2);
      laz2 = 0;
    }
  }
  
  bool apply(pl x) {
    if (x.first == 1) {
      getmod();
    } else {
      add(x.second);
    }
    return true;
  }
};

//メイン
int main(){
	
	return 0;
}
