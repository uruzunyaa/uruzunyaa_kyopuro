#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cmath>
#include<fstream>
#include<random>
using namespace std;
#define loop(i,m,n) for(int i=m;i<=n;i++)
#define rep(i,n) for (int i=0;i<n;i++)
#define ll long long
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007
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
vector<ll> makePrime(ll n) {
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
    while (k > 0) {
        if ((k&1) ==1)result=(result*n)%mod;
        n=n*n%mod;
        k >>= 1;
    }
    return result;
}

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ifstream fin("./DefaultFile");
ofstream fout("./DefaultFile");//出力する場合の出力先を指定

int main(){
	int h,w;
	cin>>h>>w;
	string a[h];
	string b[h];
	rep(i,h)cin>>a[i];
	rep(i,h)cin>>b[i];

	rep(i,h){
		rep(j,w){
			//チェック
			rep(k,h){
				if(a[k]!=b[k])break;
				if(k==h-1){
					cout<<"Yes"<<endl;
					return 0;
				}
			}

			//横回転
			rep(k,h){
				char temp=a[k][0];
				rep(l,w-1)a[k][l]=a[k][l+1];
				a[k][w-1]=temp;
			}
		}

		//縦回転
		rep(k,w){
			char temp=a[0][k];
			rep(l,h-1)a[l][k]=a[l+1][k];
			a[h-1][k]=temp;
		}
	}
	
	cout<<"No"<<endl;
    return 0;
}