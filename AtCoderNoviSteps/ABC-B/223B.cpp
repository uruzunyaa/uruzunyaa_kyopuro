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
	string s;
	cin>>s;
	ll n=s.size();
	vector<string> ans(n,s);
	loop(i,1,n-1){
		ans[i]=ans[i-1];
		ans[i].push_back(ans[i][0]);
		ans[i].erase(0,1);
	}
	sort(ans.begin(),ans.end());

	cout<<ans[0]<<endl;
	cout<<ans[n-1]<<endl;
	return 0;
}