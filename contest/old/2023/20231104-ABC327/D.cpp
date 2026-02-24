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

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
ifstream fin("./DefaultFile");
ofstream fout("./DefaultFile");//出力する場合の出力先を指定

vector<vector<int>> p(200000);
vector <int> x(200000,2);

//起点の数字を受け取り、深さ優先探索を行う関数。
//結果をxに書き込みながら、矛盾が発生したらfalseを返す関数
bool sub(int num){
	rep(i,p[num].size()){
		if(x[p[num][i]]==2){
			//まだ未探索なら、値を書き入れ、そこからさらにチェックへ
			//チェック先でも矛盾したら、falseを返す。
			x[p[num][i]]=(x[num]+1)%2;
			if(!sub(p[num][i])) return false;

		}else{
			//探索済みの場合、矛盾があるかをチェック
			//矛盾したらfalseを返して終了
			if(x[p[num][i]]==x[num]) return false;
		}
	}
	//最後まで矛盾が無かったら、trueを返す
	return true;
}

int main(){
    int n,m;
    cin>>n>>m;
    int a[m],b[m];
    rep(i,m)cin>>a[i],a[i]--;
    rep(i,m)cin>>b[i],b[i]--;

	//別グループの結びつきを記録
	rep(i,m){
		p[a[i]].push_back(b[i]);
		p[b[i]].push_back(a[i]);
	}
	
	
	rep(i,m){
		if(x[a[i]]==2){
			x[a[i]]=0;
			if(!sub(a[i])){
				cout<<"No"<<endl;
				return 0;
			}
		}
	}
	cout<<"Yes"<<endl;
    return 0;
}