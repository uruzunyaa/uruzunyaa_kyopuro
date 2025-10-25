#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>

int main() {
    ll n;
	cin>>n;
	vl a(n);
	rep(i,n){
		cin>>a[i];
	}
	sort(a.begin(),a.end());
	vector<pair<ll,ll>> s;
	s.push_back({a.front(),0});
	rep(i,n){
		if(a[i]==s.back().first)s.back().second++;
		else s.push_back({a[i],1});
	}
	ll m=s.size();

	//dp[i][j]=長さi,左端jの時の並べ方。
	vvl dp(m+1,vl(m,0));
	rep(i,n)dp[1][i]=1;

	loop(i,2,n){
		
	}
    return 0;
}