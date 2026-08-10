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
#include<atcoder/lazysegtree>


struct S{
    ll value;
    ll num;
};
using F = ll;

S op(S a, S b){
	ll nums=a.num;
	if(b.value<a.value)nums=b.num;
	else if(b.value==a.value)nums=min(a.num,b.num);
	return {min(a.value,b.value),nums};
}
S e(){ return {inf, inf}; }
S mapping(F f, S x){ return {x.value + f, x.num}; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

//メイン
int main(){
	ll t,n,d,q;
	cin>>t>>n>>d>>q;
	vl l(n),r(n);
	vector<S> v(t);
	rep(i,t){
		v[i].value=0;
		v[i].num=i;
	}
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	
	rep(i,n){
		cin>>l[i]>>r[i];
		r[i]-=d;
		l[i]++;
		r[i]=max(r[i],0LL);
		r[i]=min(r[i],l[i]);
		seg.apply(r[i],l[i],1);
	}

	while(q--){
		ll type;
		cin>>type;
		if(type==2){
			cout<<seg.prod(0,t-d+1).num<<" "<<seg.prod(0,t-d).value<<endl;
			continue;
		}
		ll i,nl,nr;
		cin>>i>>nl>>nr;
		i--;
		seg.apply(r[i],l[i],-1);
		l[i]=nl,r[i]=nr;
		r[i]-=d;
		l[i]++;
		r[i]=min(r[i],l[i]);
		r[i]=max(r[i],0LL);
		seg.apply(r[i],l[i],1);
	}

	
	return 0;
}
