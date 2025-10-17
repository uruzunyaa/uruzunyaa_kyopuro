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
	ll n,p;
	cin>>n>>p;
	string s;
	cin>>s;
	if(p==2||p==5){
		ll ans=0;
		rep(i,n){
			if((s[i]-'0')%p==0){
				ans+=i+1;
			}
		}
		cout<<ans<<endl;
		return 0;
	}
	reverse(s.begin(),s.end());
	ll sum=0;
	ll ten=1;
	vl a(p,0);
	a[0]=1;
	ll ans=0;
	rep(i,n){
		sum+=(s[i]-'0')*ten;
		sum%=p;
		ans+=a[sum];
		a[sum]++;
		ten*=10;
		ten%=p;
	}

	cout<<ans<<endl;
	return 0;
}
