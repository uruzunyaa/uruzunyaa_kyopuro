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
	vector<string> a(n);
	rep(i,n)cin>>a[i];
	vvl b(n,vl(n));
	rep(i,n)rep(j,n){
		if(a[i][j]=='D')b[i][j]=1;
		if(a[i][j]=='W')b[i][j]=2;
		if(a[i][j]=='L')b[i][j]=0;
	}
	rep(i,n)rep(j,n){
		if(i==j)continue;
		if(b[i][j]+b[j][i]!=2){
			cout<<"incorrect"<<endl;
			return 0;
		}
	}
	cout<<"correct"<<endl;
	return 0;
}