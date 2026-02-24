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
#define mod 998244353LL
//#define mod 1000000007LL

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


//メイン
int main(){
	ll n;
	cin>>n;
	vl p(n),inv(n);
	rep(i,n)cin>>p[i],p[i]--,inv[p[i]]=i;

	ordered_set<int> s;
	rep(i,n)s.insert(i);
	ll ans=0;
	for(ll i=n-1;i>=0;i--){
		ll cnt=s.order_of_key(inv[i]);

		auto it =s.find_by_order(cnt);
		s.erase(it);

		ll kosuu=i-cnt;
		ans+=kosuu*(cnt+i+1)/2;
	}
	cout<<ans<<endl;
	return 0;
}
