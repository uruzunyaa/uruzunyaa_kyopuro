//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//転倒数を求める
ll inversion_number(vl &v) {
	int n = v.size();
	if (n == 1) return 0;
	vl v1(v.begin(), v.begin() + n / 2);
	vl v2(v.begin() + n / 2, v.end());
	ll res = inversion_number(v1) + inversion_number(v2);
	int p = 0, q = 0;
	for (int i = 0; i < n; i++) {
		if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
			v[i] = v1[p++];
		}else {
			v[i] = v2[q++];
			res += v1.size() - p;
		}
    }
    return res;
}


ll solve(){
	ll n;
	cin>>n;

	if(n==0){return 1;}
	vl a(n);
	rep(i,n)cin>>a[i];

	//dp[i]=i個の要素を選んだ時現在、最後に選んだ要素が最も小さい値
	vl dp(n+1,inf);
	dp[0]=0;
	ll mx=0;

	rep(i,n){
		auto it = upper_bound(dp.begin(),dp.end(),a[i]);
		*it=a[i];
		mx=max(mx,(ll)(it-dp.begin()));
	}
	cout<<inversion_number(a)+n-mx<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
