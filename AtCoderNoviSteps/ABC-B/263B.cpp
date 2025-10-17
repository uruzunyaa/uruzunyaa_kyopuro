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
	vl a(n);
	loop(i,1,n-1)cin>>a[i],a[i]--;

	ll j=n-1;
	ll ans=0;
	while(j!=0){
		j=a[j];
		ans++;
	}
	cout<<ans<<endl;

	return 0;
}