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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>

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
	ll n,a,b,c;
	cin>>n>>a>>b>>c;
	vl dp1(n+1,0);
	dp1[0]=1;
	rep(i,n+1-a){
		dp1[i+a]+=dp1[i];
		dp1[i+a]%=mod;
	}
	rep(i,n+1-b){
		dp1[i+b]+=dp1[i];
		dp1[i+b]%=mod;
	}
	rep(i,n+1-c){
		dp1[i+c]+=dp1[i];
		dp1[i+c]%=mod;
	}
	cout<<dp1[n]<<endl;

	vl dp2(n+1,0);
	dp2[0]=1;
	rep(i,n+1-a){
		dp2[i+a]+=dp2[i];
		dp2[i+a]%=mod;
	}
	rep(i,n+1){
		dp2[i]*=ncrmd(n,i);
		dp2[i]%=mod;
	}
	rep(i,n+1-b){
		dp2[i+b]+=dp2[i];
		dp2[i+b]%=mod;
	}
	rep(i,n+1){
		dp2[i]*=ncrmd(n,i);
		dp2[i]%=mod;
	}
	rep(i,n+1-c){
		dp2[i+c]+=dp2[i];
		dp2[i+c]%=mod;
	}
	cout<<dp2[n]<<endl;
	return 0;
}
