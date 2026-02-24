//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	string s;
	cin>>s;
	ll ans=0;
	rep(i,n){
		if(i<k-1)continue;
		bool f=true;
		loop(j,i-k+1,i-1){
			if(s[i]!=s[j]){
				f=false;
				break;
			}
		}
		if(f){
			ans++;
			if(i==n-1)continue;
			if(s[i]=='A'){
				if(s[i+1]=='A')s[i]='B';
				else s[i-1]='B';
			}else{
				if(s[i+1]=='B')s[i]='A';
				else s[i-1]='A';
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}