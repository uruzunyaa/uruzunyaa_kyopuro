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
	ll n,k;
	cin>>n>>k;
	rep(i,k){
		if(n%200==0)n/=200;
		else n*=1000,n+=200;
	}
	cout<<n<<endl;
	return 0;
}