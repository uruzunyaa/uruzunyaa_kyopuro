#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,m;
	cin>>n>>m;
	vector<string> s(n);
	string t;
	set<string> r;
	rep(i,n)cin>>s[i];
	rep(i,m)cin>>t,r.insert(t);

	ll ans=0;
	rep(i,n){
		string tmp;
		loop(j,s[i].size()-3,s[i].size()-1){
			tmp.push_back(s[i][j]);
		}
		if(r.count(tmp))ans++;
	}

	cout<<ans<<endl;
	return 0;
}