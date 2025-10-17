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
	ll n;
	cin>>n;

	ll a=n/16;
	ll b=n%16;

	if(a>=10)cout<<(char)(a+'A'-10);
	else cout<<a;
	if(b>=10)cout<<(char)(b+'A'-10);
	else cout<<b;

	return 0;
}