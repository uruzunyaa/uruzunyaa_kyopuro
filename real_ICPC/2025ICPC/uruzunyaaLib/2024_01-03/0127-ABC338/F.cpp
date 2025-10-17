#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<map>//連想配列
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
#define inf 4000000000000
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
//乱数、ファイル入出力
	random_device rnd;// 非決定的な乱数生成器
	mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	ifstream fin("./DefaultFile");
	ofstream fout("./DefaultFile");//出力する場合の出力先を指定

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl wf(n,vl(n,inf));

	//ワーシャルフロイド法
	rep(i,n)wf[i][i]=0;
	rep(i,m){
		ll u,v,w;
		cin>>u>>v>>w,u--,v--;
		rep(j,n){
			rep(k,n){
				wf[j][k]=min(wf[j][k],wf[j][u]+w+wf[v][k]);
			}
		}
	}

	//b[i]=i個の1のビットを持った整数のリスト
	vvl b(n+1);
	rep(i,(1<<n)){
		ll cnt=0;
		ll tmp=i;
		rep(j,n){
			cnt+=tmp%2;
			tmp/=2;
		}
		b[cnt].push_back(i);
	}

	//dp[i][j]=i番目の節に最後に立ち寄っていて、立ち寄り済みの場所情報がbitjであるもの最小コスト
	vvl dp(n,vl((1<<n),inf));
	rep(i,n) dp[i][(1<<i)]=0;

	//dp,巡回セールスマン
	//iは既に立ち寄った節の個数
	loop(i,1,n-1){
		rep(j,b[i].size()){
			rep(k,n){
				//既に立ち寄った節だった場合スキップ
				if(b[i][j] & (1<<k))continue;
				rep(l,n){
					dp[k][b[i][j]+(1<<k)] = min(dp[k][b[i][j]+(1<<k)],dp[l][b[i][j]]+wf[l][k]);
				}
			}
		}
	}
	ll ans=inf;
	rep(i,n)ans=min(ans,dp[i][(1<<n)-1]);

	if(ans>inf/2){
		cout<<"No"<<endl;
	}else{
		cout<<ans<<endl;
	}

	return 0;
}
