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
	ll n,m;
	cin>>n>>m;
	vvl x(m);
	vvl c(n,vl(n,0));
	rep(i,m){
		ll k;
		cin>>k;
		ll t;
		rep(j,k)cin>>t,t--,x[i].push_back(t);
		rep(j,k)rep(h,k)c[x[i][j]][x[i][h]]=1;
	}
	rep(i,n)rep(j,n)if(c[i][j]==0){
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;

	return 0;
}