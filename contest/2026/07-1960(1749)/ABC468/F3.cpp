#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#include<atcoder/lazysegtree>

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//メイン
int main(){
	ll n;
	cin>>n;
	vl p(n);
	rep(i,n)cin>>p[i];
	vl v(n+1,-inf);
	v[0]=1;
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

	ll mx=p[0];
	loop(i,1,n-1){
		if(mx<p[i]){
			mx=p[i];
			seg.apply(0,n,1);
		}else{
			//mxじゃないの側を取る場合
			ll y=max(seg.prod(0,p[i])+1,seg.get(p[i]));
			seg.set(p[i],y);
		}
	}

	cout<<seg.prod(0,n)<<endl;

	return 0;
}
