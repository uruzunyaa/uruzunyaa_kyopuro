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
	vl a(n);
	rep(i,n)cin>>a[i],a[i]--;

	set<ll> ans;
	rep(i,n){
		if(!ans.count(i))ans.insert(a[i]);
	}
	cout<<n-ans.size()<<endl;
	rep(i,n){
		if(!ans.count(i))cout<<i+1<<" ";
	}
	cout<<endl;

	return 0;
}