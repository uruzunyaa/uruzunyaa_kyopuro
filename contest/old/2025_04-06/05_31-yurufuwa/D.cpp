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

#include <atcoder/segtree>
#include <cstdio>
#include <vector>

using namespace std;
using namespace atcoder;

ll op(ll a,ll b){return min(a,b);}

ll e() { return inf; }

ll target;
bool f(ll v) { return v > target; }

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	segtree<ll,op,e> seg(a);

	ll q;
	cin>>q;
	while(q--){
		ll l,r;
		cin>>l>>r;
		ll ans=a[l-1];
		while(l<r){
			target=ans;
			ll next=seg.max_right<f>(l);
			if(next>=r)break;
			ans%=a[next];
			l=next+1;

			//cout<<ans<<endl;
		}
		cout<<ans<<endl;
	}
	return 0;
}
