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
	vl a(n+1,0);

	ll aa;
	rep(i,4*n-1){
		cin>>aa;
		a[aa]++;
	}
	loop(i,1,n){
		if(a[i]==3)cout<<i<<endl;
	}
	return 0;
}