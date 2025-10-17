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
	vector<string> w(n);
	rep(i,n){
		cin>>w[i];
		if(w[i]=="and"||w[i]=="not"||w[i]=="that"||w[i]=="the"||w[i]=="you"){
			cout<<"Yes"<<endl;
			return 0;
		}

	}
	cout<<"No"<<endl;
	return 0;
}