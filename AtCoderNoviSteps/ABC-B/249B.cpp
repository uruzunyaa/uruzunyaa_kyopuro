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
	set<char> a;
	bool b=false,m=false;
	string ans="Yes";
	rep(i,s.size()){
		if(a.count(s[i]))ans="No";
		else a.insert(s[i]);
		if('a'<=s[i]&&s[i]<='z')b=true;
		else m=true;
	}
	if(!b||!m)ans="No";

	cout<<ans<<endl;
	return 0;
}