#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//using namespace atcoder;
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll int
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<int>
#define vvl vector<vector<int>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
//#define mod 998244353LL
//#define mod 1000000007LL



#include <algorithm>
#include <array>
#include <atcoder/internal_bit>
#include <atcoder/modint>
#include <cassert>
#include <type_traits>
#include <vector>


std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = static_modint<mod>;
    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) {
        a2[i] = mint(a[i]);
    }
    for (int i = 0; i < m; i++) {
        b2[i] = mint(b[i]);
    }
    auto c2 = convolution(move(a2), move(b2));
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        c[i] = c2[i].val();
    }
    return c;
}

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	ll mx=0;
	rep(i,n)cin>>a[i],mx=max(a[i],mx);

	vl bucket(mx+1,0);
	rep(i,n)bucket[a[i]]++;
	vl conv=convolution<int>(bucket,bucket);
	
	ll ans=0;
	rep(i,n){
		conv[a[i]*2]--;
		ll tmp=a[i];
		while(!(tmp&1))tmp>>=1;
		ans+=tmp;
	}
	//cout<<ans<<endl;
	loop(i,1,conv.size()-1){
		if(conv[i]==0)continue;
		//conv[i]/=2;
		ll tmp=i;
		while(!(tmp&1))tmp>>=1;
		ans+=tmp*conv[i]/2;
	}
	cout<<ans<<endl;
	return 0;
}
