//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
#define bbi boost::multiprecision::cpp_int
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
vl fact={1};
vl factinv={1};
ll ncrmd(ll n,ll r){
	while(fact.size()<=n){
		ll i=fact.size();
		fact.push_back((fact[i-1]*i)%mod);
		factinv.push_back(power_mod(fact[i],mod-2));
	}
	ll ans=fact[n];
	ans*=factinv[r];
	ans%=mod;
	ans*=factinv[n-r];
	ans%=mod;
	return ans;
}

//メイン
int main(){
	ll n,m,y;
	cin>>n>>m>>y;
	vl a(n);
	rep(i,n)cin>>a[i];

	vl lc(1LL<<n);
	lc[0]=1;
	rep(i,1LL<<n){
		ll mxbit=-1;
		rep(j,n)if((1LL<<j)&i)mxbit=j;
		loop(j,mxbit+1,n-1){
			ll gd=gcd(lc[i],a[j]);
			ll tmp=a[j]/gd;
			//tmp*lc[i]がinfを超えるならダメ
			if(inf/tmp<lc[i])lc[i+(1LL<<j)]=0;
			else lc[i+(1LL<<j)]=lcm(lc[i],a[j]);
		}
	}
	bbi ans=0;
	vector<bbi> dp(n+1,0);
	//vl dp(n+1,0);
	//ll ans=0;
	dp[m]=1;
	loop(i,m+1,n){
		bbi tmp=0;
		loop(j,m,i-1){
			tmp+=dp[j]*ncrmd(i,j);
		}
		dp[i]=-tmp;
	}
	rep(i,1LL<<n){
		if(lc[i]==0)continue;
		if(__popcount(i)<m)continue;
		ll cnt=y/lc[i];
		ans+=cnt*dp[__popcount(i)];
	}
	cout<<ans<<endl;
	//vdbg(lc);
	return 0;
}
