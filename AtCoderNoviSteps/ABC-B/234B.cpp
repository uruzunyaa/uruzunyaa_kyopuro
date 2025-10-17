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
	vl x(n),y(n);
	rep(i,n)cin>>x[i]>>y[i];

	ll mx=0;
	rep(i,n)rep(j,n){
		mx=max(mx,abs(x[i]-x[j])*abs(x[i]-x[j])+abs(y[i]-y[j])*abs(y[i]-y[j]));
	}
	cout<<fixed<<setprecision(15)<<sqrt(mx)<<endl;

	return 0;
}