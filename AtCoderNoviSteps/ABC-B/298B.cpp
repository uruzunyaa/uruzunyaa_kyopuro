#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n;
	cin>>n;
	vvl a(n,vl(n));
	vvl b(n,vl(n));
	rep(i,n)rep(j,n)cin>>a[i][j];
	rep(i,n)rep(j,n)cin>>b[i][j];

	rep(z,4){
		vvl tmp(n,vl(n));
		rep(i,n)rep(j,n)tmp[i][j]=a[n-j-1][i];
		rep(i,n)rep(j,n)a[i][j]=tmp[i][j];
		bool f=true;
		rep(i,n)rep(j,n)if(a[i][j]==1&&b[i][j]==0)f=false;
		if(f){
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}