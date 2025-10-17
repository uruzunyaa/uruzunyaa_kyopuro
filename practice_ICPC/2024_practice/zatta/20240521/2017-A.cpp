#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL

ll solve(){
	ll n,mn,mx;

	cin>>n>>mn>>mx;

	//データセット終了
	if(n==0)return 1;
	ll ans=0;
	ll m=0;
	vl p(n);
	rep(i,n)cin>>p[i];
	loop(i,mn,mx){
		if(m<=p[i-1]-p[i])m=p[i-1]-p[i],ans=i;
	}
	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}