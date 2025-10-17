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
#define mod 999999929LL

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

# define md2 1048828087LL

//逆元を返す
ll inv(ll n){
	ll k = md2-2;
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%md2;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}
// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%md2;
		n=n*n%md2;
		k >>= 1;
	}
	return result;
}

//メイン
int main(){
	ll inverse = inv(mod);
	string s;
	cin>>s;
	vl c(26);
	rep(i,26)c[i]=mt()%md2;
	ll anssiz=s.size()*2-1;
	//真ん中の文字を被らせない場合。

	ll usiro=c[s[s.size()-1]-'A'];
	ll mae  =c[s[s.size()-2]-'A'];
	if(usiro==mae)anssiz=s.size()*2-2;
	loop(i,2,s.size()/2){
		usiro*=mod;
		usiro+=c[s[s.size()-i]-'A'];
		usiro%=md2;

		mae+=md2-c[s[s.size()-i]-'A'];
		mae*=inverse;
		mae%=md2;
		mae+=power_mod(mod,i-1)*c[s[s.size()-(i*2)]-'A'];
		mae%=md2;
		mae+=power_mod(mod,i-2)*c[s[s.size()-(i*2)+1]-'A'];
		mae%=md2;
		if(usiro==mae)anssiz=min(anssiz,(ll)s.size()*2-(i*2));
	}

	usiro=c[s[s.size()-1]-'A'];
	mae  =c[s[s.size()-3]-'A'];
	if(usiro==mae)anssiz=s.size()*2-2-1;
	loop(i,2,(s.size()-1)/2){
		usiro*=mod;
		usiro+=c[s[s.size()-i]-'A'];
		usiro%=md2;

		mae+=md2-c[s[s.size()-i-1]-'A'];
		mae*=inverse;
		mae%=md2;
		mae+=power_mod(mod,i-1)*c[s[s.size()-(i*2)-1]-'A'];
		mae%=md2;
		mae+=power_mod(mod,i-2)*c[s[s.size()-(i*2)]-'A'];
		mae%=md2;
		if(usiro==mae)anssiz=min(anssiz,(ll)s.size()*2-(i*2)-1);
	}
	cout<<s;
	for(ll i=anssiz-s.size()-1;i>=0;i--)cout<<s[i];
	cout<<endl;
	return 0;
}
