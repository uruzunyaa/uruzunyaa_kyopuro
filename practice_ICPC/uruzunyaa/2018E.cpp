//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}


//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

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


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//受け取った文字列を、第2引数が0なら全て小文字に、1なら大文字に変換する関数
string cnv_string(const string &str, int mode) {
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
string cnv_base(const string &str, ll from_base, ll to_base) {
	ll num = 0;
	//小文字があったら大文字に変換
	string num_str=cnv_string(str,1);
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

string b;

//b×nを計算
string muls(ll n){
	ll bint=stoll(cnv_base(b,2,10));
	ll ans=n*bint;
	return cnv_base(to_string(ans),10,2);
}
string pluss(string x,string y){
	ll ans=stoll(cnv_base(x,2,10))+stoll(cnv_base(y,2,10));
	return cnv_base(to_string(ans),10,2);
}

ll solve(){
	ll n;
	cin>>n;
	if(n==0){return 1;}

	cin>>b;
	b.insert(b.begin(),'1');

	ll kasuu=0;
	string ans=b;
	
	while(n!=0){
		ll mn=1,mx=min(n,1LL<<(54-b.size()));

		while(mn!=mx){
			ll mid=mn+mx;
			mid/=2;
			string s=pluss(ans,muls(mid));
			if(s.size()==54)mx=mid;
			else mn=mid+1;
		}

		ans=pluss(ans,muls(mx));
		n-=mx;
		if(ans.size()==53){
			break;
		}

		ans.pop_back();
		b.pop_back();
		if(b.size()==0)b="0";
		kasuu++;
	}
	string ans1 = cnv_base(to_string(kasuu),10,2);
	while(ans1.size()!=12)ans1.insert(ans1.begin(),'0');

	cout<<ans1;
	loop(i,1,52)cout<<ans[i];
	cout<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
