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

// Union-Find
struct UnionFind {
    vector<int> par, siz;
    UnionFind(int n) : par(n, -1) , siz(n, 1) { }
    // 根を求める
    int root(int x) {
        if (par[x] == -1) return x;
        else return par[x] = root(par[x]);
    }
    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    // x を含むグループと y を含むグループとを併合する
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false; 
        if (siz[x] < siz[y]) swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    // x を含むグループのサイズ
    int size(int x) {
        return siz[root(x)];
    }
};


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
//第一引数で受け取った数を、第二引数で受け取った数の進数と見做して、第三引数の進数へ変換する。
string cnvBase(const string &str, ll from_base, ll to_base) {
	ll num = 0;
	//小文字があったら大文字に変換
	string num_str=cnvString(str,1);
	// 数値を10進数に変換
	for (char digit : num_str) {
		num = num * from_base + (isdigit(digit) ? digit - '0' : digit - 'A' + 10);
	}
	string result;
	// 数値を目的の基数に変換
	while (num > 0) {
		ll remainder = num % to_base;
		result.push_back(remainder < 10 ? remainder + '0' : remainder - 10 + 'A');
		num /= to_base;
	}
	// 結果を逆順にして返す
	reverse(result.begin(), result.end());
	return result.empty() ? "0" : result;
}
//底がaの対数xを計算
ll logax(ll a, ll x){
	ll result = 0;
	ll power = 1;
	while (power < x){
		power *= a;
		result++;
	}
	return result;
}
//乱数、ファイル入出力
	random_device rnd;// 非決定的な乱数生成器
	mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	ifstream fin("./DefaultFile");
	ofstream fout("./Segcheck");//出力する場合の出力先を指定

struct MaxSegTree{
	ll size;
	ll tall;
    vvl data;
	//コンストラクタ、セグ木に乗せる値の初期値をa配列にする。
    MaxSegTree(vl a) : data(logax(2,a.size())+1) {
		size=a.size();
		tall=logax(2,size)+1;
		ll tmp=size;
		rep(i,tall){
			data[i]=vl(tmp,-inf);
			if(i==0)rep(j,tmp)data[i][j]=a[j];
			else rep(j,tmp) data[i][j]=max(data[i-1][2*j],data[i-1][min(2*j+1,(ll)(data[i-1].size()-1))]);
			tmp=(tmp+1)/2;
		}
	}
	//更新、p番目の値をxにする。
	void update(ll p,ll x){
		rep(i,tall){
			if(i==0)data[i][p]=x;
			else data[i][p]=max(data[i-1][2*p],data[i-1][min(2*p+1,(ll)(data[i-1].size()-1))]);
			p/=2;
		}
	}
	//取得、l~r区間内の最大値を取得する。
	ll get(ll l,ll r){
		r++;
		//lとrが範囲外なら正す
		l=max(0LL,l);
		r=min(r,size);
		ll ans=-inf;
		ll h=0;
		ll po=1;
		//出来る限り上に上げきる。
		while(l+(po*2)<=r){
			while(l%(po*2)==0&&l+(po*2)<=r)h++,po*=2;
			ans=max(ans,data[h][l/po]);
			l+=po;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+po>r)h--,po/=2;
			ans=max(ans,data[h][l/po]);
			l+=po;
		}
		return ans;
	}

	//セグ木デバッグ用、丸ごと出力
	void print(){
		rep(i,size)fout<<setw(7)<<left<<i;
		fout<<endl;
		rep(i,tall){
			rep(j,size){
				if(j%power(2,i)==0)fout<<setw(7)<<left<<data[i][j/power(2,i)];
				else fout<<"       ";
			}
			fout<<endl;
		}
	}
};


//メイン
int main(){
	ll n,d;
	cin>>n>>d;
	vl a(n);
	rep(i,n)cin>>a[i];
	MaxSegTree seg(vl(600000,0));

	rep(i,n){
		ll mx=seg.get(a[i]-d,a[i]+d);
		seg.update(a[i],mx+1);
	}

	cout<<seg.get(1,500000)<<endl;
	return 0;
}
