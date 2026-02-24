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

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//left,rightはイテレーター的な挙動をする。初期値両方begin()の挙動。
struct RollingHash{
	//桁の進数
	ll md1=999999929;
	//桁の進数のinv
	ll inv=209585860;
	//管理のmod
	ll md2=1048828087;
	ll hash=0,left=0,right=0;
	ll n;
	vl s;
	unordered_map<ll,ll> stir;

	RollingHash(vl ss){
		n=ss.size();
		s=ss;
	}

	//右に一文字延長,不可能ならfalse
	bool insert_right(){
		if(right==n)return false;
		hash*=md1;
		hash%=md2;
		hash+=stir[s[right]];
		hash%=md2;
	}
	//左を一文字消去,不可能ならfalse
	bool erase_left(){
		
	}
	ll getHash(){return hash;}
	ll size(){return n;}
};

//メイン
int main(){
	
	return 0;
}
