#pragma GCC optimize("O3")
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

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl a(n,vl(n));
	rep(i,n)rep(j,n)cin>>a[i][j];

	ll ans=0;

	//真ん中の座標を決め打ち
	rep(i,n){
		//(i,n-i-1)を通る
		vl usiro;
		rep(j,n-i-1)usiro.push_back(0);
		rep(j,i)usiro.push_back(1);
		set<ll> backlist;
		do{
			ll num=0;
			ll x=i,y=n-i-1;
			rep(j,n-1){
				if(usiro[j])y++;
				else x++;
				num*=10;
				num+=a[x][y];
				num%=m;
			}
			backlist.insert(num);
		}while(next_permutation(usiro.begin(),usiro.end()));

		vl mae;
		rep(j,i)mae.push_back(0);
		rep(j,n-i-1)mae.push_back(1);
		do{
			ll num=0;
			ll x=0,y=0;
			rep(j,n-1){
				num*=10;
				num+=a[x][y];
				num%=m;
				if(mae[j])y++;
				else x++;
			}
			num*=10;
			num+=a[x][y];
			num%=m;
			rep(j,n-1){
				num*=10;
				num%=m;
			}

			auto it = backlist.lower_bound(m-num);
			if(it==backlist.begin())it=backlist.end();
			it--;
			ans=max(ans,(num+(*it))%m);
		}while(next_permutation(mae.begin(),mae.end()));
	}
	cout<<ans<<endl;
	return 0;
}
