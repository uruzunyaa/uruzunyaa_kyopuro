#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n;
	cin>>n;
	vl s(n+1);
	s[0]=0;
	loop(i,1,n)cin>>s[i];
	rep(i,n){
		cout<<s[i+1]-s[i]<<" ";
	}
	cout<<endl;
	return 0;
}