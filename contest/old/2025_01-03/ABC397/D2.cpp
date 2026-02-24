#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
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
	ll n;
	cin>>n;
	//x-yを探索
	loop(i,1,1LL<<20){
		if(n%i==0){
			ll mny=1,mxy=1LL<<30;
			while(mny<mxy){
				ll y=(mny+mxy)/2;
				ll x=y+i;
				// x^3-y^3 = (x-y)(x^2 + xy + y^2)
				ll tmp=x*x+x*y+y*y;
				
				if(tmp==n/i){
					cout<<x<<" "<<y<<endl;
					return 0;
				}
				if(tmp<n/i)mny=y+1;
				else mxy=y-1;
			}
			if(mny==mxy){
				ll y=(mny+mxy)/2;
				ll x=y+i;
				ll tmp=x*x+x*y+y*y;
				if(tmp==n/i){
					cout<<x<<" "<<y<<endl;
					return 0;
				}
			}
		}
	}
	cout<<-1<<endl;
	return 0;
}
