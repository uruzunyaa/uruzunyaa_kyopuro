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
	string s1,s2,s3;
	set<string> s;
	cin>>s1>>s2>>s3,s.insert(s1),s.insert(s2),s.insert(s3);
	if(!s.count("ABC"))cout<<"ABC";
	if(!s.count("AGC"))cout<<"AGC";
	if(!s.count("ARC"))cout<<"ARC";
	if(!s.count("AHC"))cout<<"AHC";
	return 0;
}