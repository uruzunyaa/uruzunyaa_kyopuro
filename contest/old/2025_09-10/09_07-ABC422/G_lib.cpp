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
#define md 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

#include "atcoder/convolution.hpp"

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k,ll mod){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//メイン
int main(){
	ll n,a,b,c;
	cin>>n>>a>>b>>c;
	vl dp1(n+1,0);
	dp1[0]=1;
	rep(i,n+1-a){
		dp1[i+a]+=dp1[i];
		dp1[i+a]%=md;
	}
	rep(i,n+1-b){
		dp1[i+b]+=dp1[i];
		dp1[i+b]%=md;
	}
	rep(i,n+1-c){
		dp1[i+c]+=dp1[i];
		dp1[i+c]%=md;
	}
	cout<<dp1[n]<<endl;

	vl aa={1},bb={1},cc={1};
	ll factm=1;


	loop(i,1,n){
		factm*=i;
		factm%=md;
		ll inv=power_mod(factm,md-2,md);
		
		if(i%a==0)aa.push_back(inv);
		else aa.push_back(0);

		if(i%b==0)bb.push_back(inv);
		else bb.push_back(0);

		if(i%c==0)cc.push_back(inv);
		else cc.push_back(0);
		
	}


	vl tmp = atcoder::convolution<998244353>(aa, bb);
	vl ans2= atcoder::convolution<998244353>(cc,tmp);
	cout<<(ans2[n]*factm)%md<<endl;
	return 0;
}
