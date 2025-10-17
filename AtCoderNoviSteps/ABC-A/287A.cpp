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
	ll cnt=0;
	rep(i,n){
		string s;
		cin>>s;
		if(s=="For")cnt++;
		else cnt--;
	}
	if(cnt>0)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}