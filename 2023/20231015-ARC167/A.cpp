#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 100000000000000000
//√の値が整数かを調べる
bool isSqrt(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	return sqrtN * sqrtN == n;
}
//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i = 0; i < B; i++) {
		result *= A;
	}
	return result;
}
int main(){
	ll n,m;
	cin>>n>>m;
	vector<ll>a(n);
	rep(i,n)cin>>a[i];

	sort(a.begin(),a.end());

	ll ans=0;
	rep(i,n-m){
		ans+=(a[i]+a[2*(n-m)-i-1])*(a[i]+a[2*(n-m)-i-1]);
	}
	loop(i,2*(n-m),n-1){
		ans+=a[i]*a[i];
	}
	cout<<ans<<endl;
    return 0;
}