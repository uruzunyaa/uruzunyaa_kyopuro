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
	string s;
	cin>>n>>k>>s;
	ll cnt=0;
	rep(i,n){
		if(cnt>=k)s[i]='x';
		if(s[i]=='o')cnt++;
	}
	cout<<s<<endl;
	return 0;
}