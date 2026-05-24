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
	if(n<r)return 0;
	ll anss=1;
	loop(i,1,r){
		anss*=(n%mod);
		anss%=mod;
		n--;
		anss*=power_mod(i,mod-2);
		anss%=mod;
	}
	return anss;
}

vvl g;
vl c,d;
ll ans=1;
ll dfs(ll node){
	for(const auto &val:g[node]){
		c[node]+=dfs(val);
	}
	ans*=ncrmd(c[node],d[node]);
	ans%=mod;
	return c[node]-d[node];
}

//メイン
int main(){
	ll n;
	cin>>n;
	g=vvl(n);
	loop(i,1,n-1){
		ll p;
		cin>>p;
		p--;
		g[p].push_back(i);
	}
	rep(i,n){
		ll cc;
		cin>>cc;
		c.push_back(cc);
	}
	rep(i,n){
		ll cc;
		cin>>cc;
		d.push_back(cc);
	}
	dfs(0);
	cout<<ans<<endl;
	return 0;
}
