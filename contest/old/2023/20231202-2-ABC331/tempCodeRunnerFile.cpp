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
	ll n,m,l;
	cin>>n>>m>>l;
	vl a(n);
	vl a2(n);
	vl b(m);
	vl b2(m);
	vl c(l);
	vl d(l);
	rep(i,n){
		cin>>a[i];
		a2[i]=a[i];
	}
	rep(i,m){
		cin>>b[i];
		b2[i]=b[i];
	}
	rep(i,l)cin>>c[i]>>d[i],c[i]--,d[i]--;
	map<ll,ll>kiroku;
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	vl countA(n,m-1);
	vl countB(m,n-1);
	ll indexA=n-1;
	ll indexB=m-1;
	rep(i,l+1){
		kiroku[a[indexA]+b[indexB]]++;
		countA[indexA]--;
		countB[indexB]--;
		if(indexA!=0&&indexB!=0){
			if(a[indexA-1]+b[countA[indexA-1]]<b[indexB-1]+a[countB[indexB-1]]){
				//小さくすべきはBの時
				indexA=countB[indexB-1];
				indexB--;
			}else{
				//小さくすべきはAの時
				indexB=countA[indexA-1];
				indexA--;
			}
		}else{
			if(indexA==0){
				//小さくすべきはBの時
				indexA=countB[indexB-1];
				indexB--;
			}else{
				//小さくすべきはAの時
				indexB=countA[indexA-1];
				indexA--;
			}
		}
		
	}
	rep(i,l){
		kiroku[a2[c[i]]+b2[d[i]]]--;
		if(kiroku[a2[c[i]]+b2[d[i]]]==0)kiroku.erase(a2[c[i]]+b2[d[i]]);
	}
	//range(val,kiroku)cout<<val.first<<endl;
	cout<<kiroku.rbegin()->first<<endl;
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