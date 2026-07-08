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
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

#include<atcoder/lazysegtree>

ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//nCr % mod を O(max(n)) で求める(power_mod前提条件)
//注意:先に階乗逆元等を求める関数を動かさないと
//O(Max(n log n))になる。
vl fact={1};
vl factinv={1};
void make_fact_and_factinv(ll n){
	fact=vl(n+1);
	factinv=vl(n+1);
	fact[0]=1;
	loop(i,1,n){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	factinv[n]=power_mod(fact[n],mod-2);
	rrep(i,n){
		factinv[i]=factinv[i+1]*(i+1);
		factinv[i]%=mod;
	}
}
ll ncrmd(ll n,ll r){
	if(n<r){
		return 0;
	}
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n]*factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}


struct S{
    ll value;
	ll sum;
    int size;
};
using F = long long;

S op(S a, S b){ return {(a.value+b.value+a.sum*b.sum)%mod,(a.sum+b.sum)%mod, a.size+b.size}; }
S e(){ return {0,0,0}; }
S mapping(F f, S x){ return {((x.value+ncrmd(x.size,2)*((f*f)%mod))%mod+((f*x.sum)%mod)*(x.size-1))%mod,(x.sum + f*x.size)%mod, x.size}; }
F composition(F f, F g){ return (f+g)%mod; }
F id(){ return 0; }

int main(){
	ll n,q;
	cin>>n>>q;
	make_fact_and_factinv(n);
	vector<S> v(n,{0,0,1});
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);
	while(q--){
		ll l,r,a;
		cin>>l>>r>>a;
		l--;
		seg.apply(l,r,a);
		// rep(i,n){
		// 	cout<<seg.get(i).sum<<" ";
		// }
		// cout<<endl;
		cout<<seg.prod(l,r).value<<endl;
	}
}