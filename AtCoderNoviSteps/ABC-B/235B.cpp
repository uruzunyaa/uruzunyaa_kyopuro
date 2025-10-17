#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	ll n;
	cin>>n;
	vl h(n);
	rep(i,n)cin>>h[i];
	ll ans=h[0];
	loop(i,0,n-2){
		if(h[i]<h[i+1])ans=h[i+1];
		else break;
	}
	cout<<ans<<endl;
	return 0;
}