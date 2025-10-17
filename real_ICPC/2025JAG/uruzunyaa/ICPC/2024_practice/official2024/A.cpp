// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#include<atcoder/all>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

ll solve(){
	ll n;
	cin >> n;
	if(n == 0)return 1;

	vector<ll> A(n);
	for (ll i = 0; i < n; ++i) cin >> A[i];

	ll now = 0;
	ll rem = 300;

	for (ll i = 0; i < n; ++i) {
		if (rem >= A[i]) {
			now += A[i];
			rem -= A[i];
		} else {
			continue;
		}
	}

	cout << now << endl;

	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}