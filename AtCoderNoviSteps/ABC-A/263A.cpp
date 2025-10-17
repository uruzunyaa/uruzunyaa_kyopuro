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
	ll a[5];
	rep(i,5)cin>>a[i];
	sort(a,a+5);
	if(a[0]==a[1]&&a[0]==a[2]&&a[0]!=a[3]&&a[3]==a[4])cout<<"Yes"<<endl;
	else if(a[0]==a[1]&&a[0]!=a[2]&&a[2]==a[3]&&a[3]==a[4]) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}