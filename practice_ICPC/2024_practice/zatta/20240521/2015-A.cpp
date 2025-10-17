#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353

ll solve(){
	ll n;
	cin>>n;
	if(n==0)return 1;

	vl a(n);
	rep(i,n)cin>>a[i];

	sort(a.begin(),a.end());
	ll ans=inf;
	rep(i,n-1)ans=min(ans,a[i+1]-a[i]);

	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}