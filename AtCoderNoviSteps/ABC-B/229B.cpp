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
	string a,b;
	cin>>a>>b;
	rep(i,min(a.size(),b.size())){
		if(a[a.size()-i-1]-'0'+b[b.size()-i-1]-'0'>9){
			cout<<"Hard"<<endl;
			return 0;
		}
	}
	cout<<"Easy"<<endl;
	return 0;
}