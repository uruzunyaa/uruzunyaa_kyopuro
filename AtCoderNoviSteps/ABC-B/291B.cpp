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
	vl x(n*5);
	double sum=0;
	rep(i,n*5)cin>>x[i];
	sort(x.begin(),x.end());
	loop(i,n,n*4-1)sum+=x[i];
	sum /= n*3;
	cout<<sum<<endl;
	return 0;
}