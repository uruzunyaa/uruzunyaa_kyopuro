#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

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

//map形式で、nを素因数分解した値を返す
map<ll,ll> makeMapPrime(ll n){
	map<ll,ll> factors;
	while (n % 2 == 0) {
		factors[2]++;
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors[i]++;
			n /= i;
		}
	}
	if (n > 2) {
		factors[n]++;
	}
	return factors;
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

//mod mにおけるaの逆元を計算
ll modinv(ll a, ll m) {
	ll b = m, u = 1, v = 0;
	while (b) {
		ll t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m; 
	if (u < 0) u += m;
	return u;
}

//場合の数 nCr を求める
ll ncr(ll n,ll r) {
	if(n<r)return 0;
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

//底がaの対数xを計算。ただし小数点は繰り上げ。
ll logax(ll a, ll x){
	if(x<=1)return 0;
	ll result = 1;
	ll power = 1;
	while (power < (x+a-1) / a){
		power *= a;
		result++;
	}
	return result;
}

//第一引数を第二引数で割った余りを計算、割る数はint範囲
ll bigmd(const string &num, int md) {
	ll ans = 0;
	ll SIZ = 9; //9桁のチャンク
	ll base = 1000000000;//SIZ個の0
	rep(i,(num.size()-1)/SIZ+1){
		ll chunk = 0;
		ll l = i*SIZ;
		ll r = min((ll)num.size(),l+SIZ);
		if(r!=num.size()){
			ans = (ans*base+stoll(num.substr(l,r-l)))%md;
		}else{
			rep(i,r-l)ans*=10;
			ans=(ans+stoll(num.substr(l,r-l)))%md;
		}
	}
	return ans;
}

//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

//ax+by=cの整数解を得る ただし、cはgcd(a,b)の倍数でない場合、0,0になる
pair<ll,ll> ex_euclid(ll a,ll b,ll c){
	if(a<0||b<0||c<0){
		pair<ll,ll>ans=ex_euclid(abs(a),abs(b),abs(c));
		if(a<0)ans.first*=-1;
		if(b<0)ans.second*=-1;
		if(c<0)ans.first*=-1,ans.second*=-1;
		return ans;
	}
	if(c!=1){
		ll d=gcd(a,b);
		if(c%d!=0)return make_pair(0,0);
		pair<ll,ll>ans = ex_euclid(a/d,b/d,1);
		ans.first*=c/d;
		ans.second*=c/d;
		return ans;
	}
	if(a<b){
		pair<ll,ll>ans=ex_euclid(b,a,c);
		swap(ans.first,ans.second);
		return ans;
	}
	if(a==1&&b==0)return make_pair(1,0);
	else if(b==0) return make_pair(0,0);
	ll x,y;
	tie(x,y)=ex_euclid(b,a%b,c);
	pair<ll,ll> ans=make_pair(y,x-(a/b)*y);
	return ans;
}

//オイラーのトーシェント関数。N以下のNと互いに素な物の数を返す。
ll euler(ll n){
	unordered_map<ll,ll> factors;
	ll tmp=n;
	while (tmp % 2 == 0) {
		factors[2]++;
		tmp /= 2;
	}
	for (ll i=3; i*i<=tmp;i+=2) {
		while (tmp%i == 0) {
			factors[i]++;
			tmp/= i;
		}
	}
	if (tmp > 2)factors[tmp]++;
	ll ans=1;
	for(const auto & val:factors){
		ans*=power(val.first,val.second-1)*(val.first-1);
	}
	return ans;
}

// Union-Find
struct UnionFind {
	vector<int> par, siz,mx,mn,color;
	UnionFind(int n) : par(n, -1) , siz(n, 1) {
		rep(i,n){
			mx.push_back(i);
			mn.push_back(i);
			color.push_back(i);
		}
	}
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
		mx[x]=max(mx[x],mx[y]);
		mn[x]=min(mn[x],mn[y]);
		return true;

	}
	void chengecolor(int x, int c){
		x=root(x);
		color[x]=c;
	}
	// xを含むグループの最小値
	int mini(int x){
		x=root(x);
		return mn[x];
	}
	// xを含むグループの最大値
	int maxi(int x){
		x=root(x);
		return mx[x];
	}
	// xの色
	int getcolor(int x){
		x=root(x);
		return color[x];
	}

	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//乱数、ファイル入出力
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	UnionFind uf(n);
	vl ans(n,1);
	while(q--){
		ll t;
		cin>>t;
		if(t==1){
			ll x,c;
			cin>>x>>c;
			x--,c--;
			ans[uf.getcolor(x)]-=uf.size(x);
			ans[c]+=uf.size(x);
			uf.chengecolor(x,c);
			if(uf.mini(x)!=0){
				if(uf.getcolor(uf.mini(x)-1)==uf.getcolor(x)){
					uf.unite(uf.mini(x)-1,x);
				}
			}
			if(uf.maxi(x)!=n-1){
				if(uf.getcolor(uf.maxi(x)+1)==uf.getcolor(x)){
					uf.unite(uf.maxi(x)+1,x);
				}
			}
		}else{
			ll c;
			cin>>c;
			c--;
			cout<<ans[c]<<endl;
		}
	}	
	return 0;
}
