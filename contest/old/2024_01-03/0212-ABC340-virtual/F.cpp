#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<set>//セット
#include<unordered_set>//ハッシュセット
#include<map>//木構造マップ
#include<unordered_map>//ハッシュマップ
#include<deque>//スタックとキュー
#include<iomanip>//出力形式調整
#include<tuple>//pairの複数型
#include<cmath>//数学。ルートとか
#include<cctype>//大文字小文字のチェックなど
#include<fstream>//ファイル入出力
#include<random>//乱数
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

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k) {
	ll result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}
// 2つの数値の乗算を安全に行い、モジュロmでの結果を返す関数
ll safe_mod_mul(ll a, ll b, ll m) {
    ll result = 0;
    a %= m;
    while (b) {
        // bの最下位ビットが1の場合、aを結果に加える
        if (b & 1) {
            result = (result + a) % m;
        }
        // aを2倍し、bを1ビット右にシフトする
        a = (a * 2) % m;
        b >>= 1;
    }
    return result;
}

// nのk乗をmで割った余りを計算する関数
// mが大きく、n*nがll型を超える可能性がある場合に対応
ll long_power_mod(ll n, ll k, ll m) {
    ll result = 1;
    n %= m; // nをモジュロmでの剰余に変換
    while (k > 0) {
        // kの最下位ビットが1の場合、resultにnを掛ける
        if (k & 1) {
            result = safe_mod_mul(result, n, m);
        }
        // nを自身に掛けてn^2を計算し、kを1ビット右にシフト
        n = safe_mod_mul(n, n, m);
        k >>= 1;
    }
    return result;
}

//メイン
int main(){

	ll x,y,t;
	cin>>x>>y;
	t=gcd(x,y);
	if(t>2){
		cout<<-1<<endl;
		return 0;
	}
	if(x==0&&y==0){
		cout<<-1<<endl;
		return 0;
	}
	if(x==0&&-3<y&&y<3){
		cout<<2/y<<" "<<0<<endl;
		return 0;
	}
	if(y==0&&-3<x&&x<3){
		cout<<0<<" "<<2/x<<endl;
		return 0;
	}
	if(x==0||y==0){
		cout<<-1<<endl;
		return 0;
	}
	x/=t;
	y/=t;
	
	ll a=(long_power_mod(y,x-2,x)*(2/t))%x;
	ll b=(a*y-2/t)/x;

	cout<<a<<" "<<b<<endl;
	
	return 0;
}
