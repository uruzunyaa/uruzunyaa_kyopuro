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
	ll n,k;
	cin>>n>>k;
	vl x(n);
	vl y(n);
	rep(i,n)cin>>x[i]>>y[i];

	ll sMax=1000000000;
	ll sMin=0;

	while(sMin!=sMax){
		ll sMid=(sMin+sMax)/2;

		ll pMin=0;
		ll pMax=1000000000-sMid;
		ll moveX=inf;
		ll move0=0;
		ll move3=0;
		rep(i,n){
			if(x[i]<pMin){
				move0+=pMin-x[i];
			}else if(x[i]>pMin+sMid){
				move0+=x[i]-pMin-sMid;
			}
		}
		rep(i,n){
			if(x[i]<pMax){
				move3+=pMax-x[i];
			}else if(x[i]>pMax+sMid){
				move3+=x[i]-pMax-sMid;
			}
		}
		while(pMax-pMin>1){
			ll pMid1=(pMin*2+pMax)/3;
			ll pMid2=(pMin+pMax*2)/3;
			ll move1=0;
			rep(i,n){
				if(x[i]<pMid1){
					move1+=pMid1-x[i];
				}else if(x[i]>pMid1+sMid){
					move1+=x[i]-pMid1-sMid;
				}
				if(move1>inf)break;
			}
			ll move2=0;
			rep(i,n){
				if(x[i]<pMid2){
					move2+=pMid2-x[i];
				}else if(x[i]>pMid2+sMid){
					move2+=x[i]-pMid2-sMid;
				}
				if(move2>inf)break;
			}
			
			moveX=min(moveX,min(min(move0,move1),min(move2,move3)));
			if(pMin==pMid1)break;
			if(move0<move1){
				pMax=pMid1;
				move3=move1;
			}else if(move1<move2){
				pMax=pMid2;
				move3=move2;
			}else if(move2<=move3){
				pMin=pMid1;
				move0=move1;
			}else{
				pMin=pMid2;
				move0=move2;
			}
		}
		pMin=0;
		pMax=1000000000-sMid;
		ll moveY=inf;
		move0=0;
		move3=0;
		rep(i,n){
			if(y[i]<pMin){
				move0+=pMin-y[i];
			}else if(y[i]>pMin+sMid){
				move0+=y[i]-pMin-sMid;
			}
		}
		rep(i,n){
			if(y[i]<pMax){
				move3+=pMax-y[i];
			}else if(y[i]>pMax+sMid){
				move3+=y[i]-pMax-sMid;
			}
		}
		while(pMax-pMin>1){
			ll pMid1=(pMin*2+pMax)/3;
			ll pMid2=(pMin+pMax*2)/3;
			ll move1=0;
			rep(i,n){
				if(y[i]<pMid1){
					move1+=pMid1-y[i];
				}else if(y[i]>pMid1+sMid){
					move1+=y[i]-pMid1-sMid;
				}
				if(move1>inf)break;
			}
			ll move2=0;
			rep(i,n){
				if(y[i]<pMid2){
					move2+=pMid2-y[i];
				}else if(y[i]>pMid2+sMid){
					move2+=y[i]-pMid2-sMid;
				}
				if(move2>inf)break;
			}
			
			moveY=min(moveY,min(min(move0,move1),min(move2,move3)));
			if(pMin==pMid1)break;
			if(move0<move1){
				pMax=pMid1;
				move3=move1;
			}else if(move1<move2){
				pMax=pMid2;
				move3=move2;
			}else if(move2<=move3){
				pMin=pMid1;
				move0=move1;
			}else{
				pMin=pMid2;
				move0=move2;
			}
		}
		if(moveX+moveY>k){
			sMin=sMid+1;
		}else{
			sMax=sMid;
		}
	}
	cout<<sMin<<endl;
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