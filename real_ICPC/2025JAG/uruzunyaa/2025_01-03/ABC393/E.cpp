#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll int
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

//メイン
int main(){
	ll mx=1000000;

	ll n,k;
	cin>>n>>k;
	vl a(n);
	vl cnt(mx+1,0);
	vl bucket(mx+1,0);
	vl ans(mx+1,1);
	rep(i,n){
		cin>>a[i];
		bucket[a[i]]++;
	}

	loop(i,1,mx){
		for(ll j=i;j<=mx;j+=i){
			cnt[i]+=bucket[j];
		}
	}

	loop(i,1,mx){
		if(cnt[i]>=k){
			for(ll j=i;j<=mx;j+=i)ans[j]=i;
		}
	}

	rep(i,n){
		cout<<ans[a[i]]<<endl;
	}

	return 0;
}
