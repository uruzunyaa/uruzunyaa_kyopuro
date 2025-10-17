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
	ll n,k;
	cin>>n>>k;
	ll aa;
	set<ll> a;
	rep(i,k)cin>>aa,a.insert(aa-1);
	vl x(n);
	vl y(n);
	rep(i,n)cin>>x[i]>>y[i];

	ll mx=0;
	rep(i,n){
		ll mn=inf;
		rep(j,n){
			if(a.count(j)){
				mn=min(mn,abs(x[i]-x[j])*abs(x[i]-x[j])+abs(y[i]-y[j])*abs(y[i]-y[j]));
			}
		}
		mx=max(mx,mn);
	}

	cout<<fixed<<setprecision(15)<<sqrt(mx)<<endl;
	return 0;
}