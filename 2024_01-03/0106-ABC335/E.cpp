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
//乱数、ファイル入出力
	random_device rnd;// 非決定的な乱数生成器
	mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	ifstream fin("./DefaultFile");
	ofstream fout("./DefaultFile");//出力する場合の出力先を指定

//メイン
int main(){
	//入力
	ll n,m;
	cin>>n>>m;
	vl a(n);
	rep(i,n)cin>>a[i];
	vl u(m),v(m);
	rep(i,m)cin>>u[i]>>v[i],u[i]--,v[i]--;
	
	//UnionFindを用いて、同じ整数で繋がっている物を判定。
	UnionFind uf(n);
	rep(i,m)if(a[u[i]]==a[v[i]])uf.unite(u[i],v[i]);

	//小さい値から大きい値への有向グラフとして作成。
	//同値で繋がっている物は一つのノードにまとめる。
	vvl g(n);
	rep(i,m){
		if(a[u[i]]>a[v[i]]){
			g[uf.root(v[i])].push_back(uf.root(u[i]));
		}else if(a[u[i]]<a[v[i]]){
			g[uf.root(u[i])].push_back(uf.root(v[i]));
		}
	}

	//インデックスをmapに記録
	map<ll,vl> ls;
	rep(i,n)if(a[0]<=a[i]&&a[i]<=a[n-1])ls[a[i]].push_back(i);

	//dpを用いて各ノードの値を保管
	vl dp(n,0);
	dp[uf.root(0)]=1;
	//mapを見ながら小さい順に調査。
	range(pir,ls){
		rep(i,pir.second.size()){
			//dpが確定しているノード
			ll kNode=uf.root(pir.second[i]);

			//未到達ノードだったらこの先を実行しない。
			if(dp[kNode]==0)continue;
			
			//最大値を採用する。
			rep(j,g[kNode].size()){
				dp[g[kNode][j]]=max(dp[g[kNode][j]],dp[kNode]+1);
			}
		}
	}

	cout<<dp[uf.root(n-1)]<<endl;
	return 0;
}
