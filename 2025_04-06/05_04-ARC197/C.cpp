
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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;


//答えのmaxは2750171
#define inf 2750171

//メイン
int main(){
	ordered_set<int> s;
	loop(i,1,inf)s.insert(i);
	int q;
	cin>>q;
	while(q--){
		int a,b;
		cin>>a>>b;
		b--;
		if(a<=inf){
			for(int i=a;i<=inf;i+=a){
				s.erase(i);
			}
		}
		cout<<*s.find_by_order(b)<<endl;
	}
	return 0;
}
