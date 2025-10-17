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
	string s;
	cin>>s;
	rep(i,s.size()/2){
		swap(s[i*2],s[i*2+1]);
	}
	cout<<s<<endl;
	return 0;
}