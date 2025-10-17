#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	ll n,m;
	cin>>n>>m;

	vector<string> s(n);
	rep(i,n)cin>>s[i];

	sort(s.begin(),s.end());
	do{
		bool ok=true;
		rep(i,n-1){
			ll cnt=0;
			rep(j,m){
				if(s[i][j]!=s[i+1][j])cnt++;
			}
			if(cnt!=1)ok=false;
		}
		if(ok){
			cout<<"Yes"<<endl;
			return 0;
		}
	}while(next_permutation(s.begin(),s.end()));
	cout<<"No"<<endl;
	return 0;
}