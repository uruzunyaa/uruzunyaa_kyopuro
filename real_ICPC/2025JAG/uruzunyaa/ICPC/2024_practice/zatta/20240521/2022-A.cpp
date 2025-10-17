#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL


ll solve(){
	ll n;
	cin>>n;
	if(n==0)return 1;

	vl b(n);
	rep(i,n)cin>>b[i];
	ll ans=0;
	loop(i,1,n-2)if(b[i-1]<b[i]&&b[i]>b[i+1])ans++;
	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}