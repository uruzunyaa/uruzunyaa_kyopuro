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
	vl a(n),b(n);
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];
	ll ans1=0,ans2=0;

	rep(i,n){
		if(a[i]==b[i])ans1++;
	}
	rep(i,n)rep(j,n){
		if(a[i]==b[j])ans2++;
	}
	cout<<ans1<<endl<<ans2-ans1<<endl;

	return 0;
}