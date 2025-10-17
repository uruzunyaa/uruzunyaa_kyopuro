#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
vl dx={1,0,-1,0};
vl dy={0,-1,0,1};
int main(){
	ll n;
	string t;
	cin>>n>>t;
	ll x=0,y=0,m=0;
	rep(i,n){
		if(t[i]=='S')x+=dx[m],y+=dy[m];
		else m++,m%=4;
	}
	cout<<x<<" "<<y<<endl;
	return 0;
}