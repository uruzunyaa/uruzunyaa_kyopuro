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
	ll n,x;
	cin>>n>>x;
	vl a(n+1);
	a[0]=0;
	
	ll ans=0;
	loop(i,1,n){
		cin>>a[i];
		if(a[i]+a[i-1]>x){
			ans+=a[i]+a[i-1]-x;
			a[i]-=a[i]+a[i-1]-x;
		}
	}
	cout<<ans<<endl;
	return 0;
}