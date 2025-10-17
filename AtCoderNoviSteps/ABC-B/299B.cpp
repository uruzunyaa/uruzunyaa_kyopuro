#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,t;
	cin>>n>>t;
	vl c(n),r(n);
	rep(i,n)cin>>c[i];
	rep(i,n)cin>>r[i];

	ll ans=0;
	bool f=true;
	rep(i,n)if(c[i]==t)f=false,ans=i;
	if(f)t=c[0];

	
	rep(i,n){
		if(c[i]==t&&r[i]>r[ans])ans=i;
	}
	cout<<ans+1<<endl;
	return 0;
}