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
	vector<string> s(4);
	string t;
	cin>>s[1]>>s[2]>>s[3]>>t;
	rep(i,t.size()){
		cout<<s[t[i]-'0'];
	}
	return 0;
}