#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll unsigned long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


//乱数、ファイル入出力
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//メイン
int main(){
	set<ll> cube;
	loop(i,1,1LL<<15){
		cube.insert(i*i*i);
	}
	ll n;
	cin>>n;

	auto it=cube.begin();
	ll cnt=1;
	while(it!=cube.end()){
		ll x=*it;
		if(x<=n){
			it++;
			cnt++;
			continue;
		}
		if(cube.count(x-n)){
			cout<<cnt<<" ";
			loop(i,1,inf){
				if(i*i*i==x-n){
					cout<<i<<endl;
					return 0;
				}
			}
		}
		it++;
		cnt++;
	}
	cout<<-1<<endl;
	return 0;
}
