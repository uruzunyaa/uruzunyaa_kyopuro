#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

vl bikkuri(4000001,1);

ll ncrmd(ll n,ll r){
	ll ans=bikkuri[n];
	ans*=power_mod(bikkuri[r],mod-2);
	ans%=mod;
	ans*=power_mod(bikkuri[n-r],mod-2);
	ans%=mod;
	return ans;
}

//メイン
int main(){
	
	loop(i,1,4000000){
		bikkuri[i]=bikkuri[i-1]*i;
		bikkuri[i]%=mod;
	}

	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	
	ll ans=0;

	//dのcに対する左端
	rep(i,c+1){
		//dの挿入の通り
		ll tmp=ncrmd(c-i+d-1,c-i);
		//bの挿入の通り
		tmp*=ncrmd(a+i+b,b);
		tmp%=mod;
		ans+=tmp;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
