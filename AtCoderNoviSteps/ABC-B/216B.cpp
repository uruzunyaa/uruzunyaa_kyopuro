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
	string d;
	set<string> m;
	getline(cin,d);
	rep(i,n){
		getline(cin,d);
		if(m.count(d)){
			cout<<"Yes"<<endl;
			return 0;
		}
		m.insert(d);
	}
	cout<<"No"<<endl;
	return 0;
}