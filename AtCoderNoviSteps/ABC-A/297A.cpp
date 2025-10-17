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
	ll n,d;
	cin>>n>>d;
	vl a(n);
	rep(i,n)cin>>a[i];
	rep(i,n-1){
		if(a[i+1]-a[i]<=d){
			cout<<a[i+1]<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}