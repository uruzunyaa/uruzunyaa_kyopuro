#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll t;
	cin>>t;
	rep(z,t){
		ll n;
		cin>>n;
		ll a;
		ll ans=0;
		rep(i,n){
			cin>>a;
			if(a%2==1)ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}