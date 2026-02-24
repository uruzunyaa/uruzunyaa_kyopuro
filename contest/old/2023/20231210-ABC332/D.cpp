#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
#include<cctype>
#include<fstream>
#include<random>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007

//関数
	bool isSqrt(ll);
	ll power(ll,ll);
	vector<ll> makePrime(ll);
	ll power_mod(ll,ll);
	ll ncr(ll,ll);
	string cnvString(const string &str, int mode);
//乱数、ファイル入出力
	random_device rnd;// 非決定的な乱数生成器
	mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	ifstream fin("./DefaultFile");
	ofstream fout("./DefaultFile");//出力する場合の出力先を指定


//メイン
int main(){
	ll h,w;
	cin>>h>>w;
	vvl a(h,vl(w,0));
	vvl b(h,vl(w,0));
	rep(i,h)rep(j,w)cin>>a[i][j];
	rep(i,h)rep(j,w)cin>>b[i][j];

	vl hs(h);
	rep(i,h)hs[i]=i;
	vl ws(w);
	rep(i,w)ws[i]=i;

	ll mn=inf;
	do{
	do{
		ll cost=0;
		//vvl c(h,vl(w,0));
		ll flag=0;
		rep(i,h){
			rep(j,w){
				if(b[i][j]!=a[hs[i]][ws[j]])flag=1;
			}
		}
		if(flag==1)continue;
		vl nhs(h);
		rep(i,h)nhs[i]=i;
		vl nws(w);
		rep(i,w)nws[i]=i;
		rep(i,h){
			auto it=lower_bound(nhs.begin(),nhs.end(),hs[i]);
			cost+=it-nhs.begin();
			nhs.erase(it);
		}
		rep(i,w){
			auto it=lower_bound(nws.begin(),nws.end(),ws[i]);
			cost+=it-nws.begin();
			nws.erase(it);
		}
		mn=min(mn,cost);

    } while (next_permutation(ws.begin(),ws.end()));
    } while (next_permutation(hs.begin(),hs.end()));
	if(mn==inf){
		cout<<-1<<endl;
	}else{
		cout<<mn<<endl;
	}
	return 0;
}


//√の値が整数かを調べる
bool isSqrt(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	return sqrtN * sqrtN == n;
}
//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}
//素因数分解
vector<ll> makePrime(ll n){
	vector<ll> factors;
	while (n % 2 == 0) {
		factors.push_back(2);
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors.push_back(i);
			n /= i;
		}
	}
	if (n > 2) {
		factors.push_back(n);
	}
	return factors;
}
// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k) {
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}
//場合の数 nCr を求める
ll ncr(ll n,ll r) {
	vvl dp(n+1,vl(r+1));
	rep (i,n+1)dp[i][0] = 1;
	rep (i,r+1)dp[i][i] = 1;
	loop (i,1,n){
		loop (j,1,min((ll)i-1,r)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
		}
	}
	return dp[n][r];
}
//受け取った文字列を、第2引数が0なら全て小文字に、1なら大文字に変換する関数
string cnvString(const string &str, int mode) {
	string result = str;
	if (mode == 0) {
		// 小文字に変換
		for (char &c : result) {
			c = tolower(c);
		}
	} else if (mode == 1) {
		// 大文字に変換
		for (char &c : result) {
			c = toupper(c);
		}
	}
	return result;
}