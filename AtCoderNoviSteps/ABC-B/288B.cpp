#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,k;
	cin>>n>>k;
	vector<string> s(k);
	rep(i,k)cin>>s[i];
	sort(s.begin(),s.end());
	rep(i,k)cout<<s[i]<<endl;
	return 0;
}