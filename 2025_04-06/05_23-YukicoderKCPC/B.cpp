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



//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

ll introot(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	ll ans=0;
	loop(i,max(0LL,sqrtN-2),sqrtN+2){
		if(i * i <= n)ans=i;
	}
	return ans;
}

//メイン
int main(){
	ll k,n;
	cin>>k>>n;
	set<ll> ans;
	for(ll x=1;power(x,6)<n;x++){
		for(ll y=1;power(y,4)+power(x,6)<=n;y++){
			ll tmp=power(y,4)+power(x,6);
			if(tmp%k!=0)continue;
			tmp/=k;
			if(power(introot(tmp),2)!=tmp)continue;
			ans.insert(tmp*k);
		}
	}
	cout<<ans.size()<<endl;
	//setdbg(ans);
	return 0;
}
