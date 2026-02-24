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

#include"atcoder/lazysegtree"

namespace RangeUpdateChgcdRangeMaxSum {

constexpr uint32_t BINF = 1 << 30;
struct S {
    uint32_t max;    // 区間最大値
    uint32_t lcm;    // min(BINF, (区間内全要素の最小公倍数))
    uint32_t sz;     // 区間要素数
    uint64_t sum;    // 区間内全要素の総和
    bool fail;
    S() : max(0), lcm(1), sz(0), sum(0), fail(0) {}
    S(uint32_t x, uint32_t sz_ = 1) : max(x), lcm(x), sz(sz_), sum((uint64_t)x * sz_), fail(0) {}
};

S e() { return S(); }

S op(S l, S r) {
    if (r.sz == 0) return l;
    if (l.sz == 0) return r;
    S ret;
    ret.max = std::max(l.max, r.max);
    ret.sum = l.sum + r.sum;
    ret.lcm = std::min(uint64_t(BINF), (uint64_t)l.lcm * r.lcm / std::__gcd(l.lcm, r.lcm));
    ret.sz = l.sz + r.sz;
    return ret;
}

struct F {
    uint32_t dogcd, reset;
    F() : dogcd(0), reset(0) {}
    F(uint32_t g, uint32_t upd) : dogcd(g), reset(upd) {}
    static F gcd(uint32_t g) noexcept { return F(g, 0); }
    static F update(uint32_t a) noexcept { return F(0, a); }
};

F composition(F fnew, F fold) {
    if (fnew.reset) return F::update(fnew.reset);
    else if (fold.reset) {
        return F::update(std::__gcd(fnew.dogcd, fold.reset));
    } else {
        return F::gcd(std::__gcd(fnew.dogcd, fold.dogcd));
    }
}

F id() { return F(); }

S mapping(F f, S x) {
    if (x.fail) return x;
    if (f.reset) x = S(f.reset, x.sz);
    if (f.dogcd) {
        if (x.sz == 1) {
            x = S(std::__gcd(x.max, f.dogcd));
        } else if (x.lcm == BINF or f.dogcd % x.lcm) {
            // 区間 gcd クエリによって，複数個の要素からなる区間で
            // いずれかの値が変更を受ける場合のみ計算失敗
            x.fail = true;
        }
    }
    return x;
}
using segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
} // namespace RangeUpdateChgcdRangeMaxSum

//メイン
int main(){
	
	return 0;
}
