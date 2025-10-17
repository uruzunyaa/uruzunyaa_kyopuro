//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
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

#include"atcoder/lazysegtree.hpp"

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

int main(){
    int n,q;
	cin>>n>>q;
    vl v(n,0);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	while(q--){
		ll a,b;
		cin>>a>>b;
		a--;
		ll acnt=seg.get(a);
		ll bcnt=seg.get(b-1);
		if(acnt!=bcnt){
			cout<<"No"<<endl;
			continue;
		}
		ll mn=seg.prod(a,b);
		if(acnt!=mn){
			cout<<"No"<<endl;
			continue;
		}
		cout<<"Yes"<<endl;
		seg.apply(a+1,b-1,1);
	}
}