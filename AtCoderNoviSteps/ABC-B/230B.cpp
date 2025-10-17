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
	string t="oxxoxxoxxoxxoxxoxxoxx";
	string s;
	cin>>s;
	if(t.find(s)==string::npos)cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	return 0;
}