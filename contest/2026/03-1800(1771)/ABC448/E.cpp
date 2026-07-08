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

#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


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

//nがk個
ll repuni_mod(ll n, ll k,ll mod){
	long long result = 0;
	ll cnt=1;
	ll tmp=n;
	while (k > 0){
		ll zero=power_mod(10,cnt,mod);
		if ((k&1) ==1){
			result*=zero;
			result+=tmp;
			result%=mod;
		}
		tmp=tmp+zero*tmp;
		tmp%=mod;
		k >>= 1;
		cnt*=2;
	}
	return result;
}


//メイン
int main(){
	ll k,m;
	cin>>k>>m;
	ll mod=m*10007;
	ll ans=0;
	
	rep(i,k){
		ll c,l;
		cin>>c>>l;
		ans*=power_mod(10,l,mod);
		ans%=mod;
		ans+=repuni_mod(c,l,mod);
		ans%=mod;
	}
	ans/=m;
	cout<<ans<<endl;
	return 0;
}
