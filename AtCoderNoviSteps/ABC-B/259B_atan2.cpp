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
	double a,b,d;
	cin>>a>>b>>d;
	double c=sqrt(a*a+b*b);

	double theta=atan2(b,a);
	theta += d/180.0*M_PI;

	cout<<fixed<<setprecision(15)<<cos(theta)*c<<" "<<sin(theta)*c<<endl;

	return 0;
}