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
	string x;
	cin>>x;
	string t="01234567890123";
	string ans="Strong";
	if(t.find(x)!=string::npos)ans="Weak";
	if(x[0]==x[1]&&x[0]==x[2]&&x[0]==x[3])ans="Weak";
	cout<<ans<<endl;
	return 0;
}