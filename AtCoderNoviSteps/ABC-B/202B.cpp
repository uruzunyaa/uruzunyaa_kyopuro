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
	rep(i,s.size()){
		if(s[s.size()-i-1]=='6')cout<<"9";
		else if(s[s.size()-i-1]=='9')cout<<"6";
		else cout<<s[s.size()-i-1];
	}
	return 0;
}