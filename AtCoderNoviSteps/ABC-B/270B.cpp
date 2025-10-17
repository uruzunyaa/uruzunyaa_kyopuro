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
	ll x,y,z;
	cin>>x>>y>>z;

	if(x<0)x*=-1,y*=-1,z*=-1;

	if(y<x&&y>0){
		if(y<z){
			cout<<-1<<endl;
		}else{
			ll ans=abs(z)+x-z;
			cout<<ans<<endl;
		}
	}else{
		cout<<x<<endl;
	}
	
	return 0;
}