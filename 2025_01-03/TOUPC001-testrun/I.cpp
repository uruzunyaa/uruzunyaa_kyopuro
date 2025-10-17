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

//重み付きUF
struct PotentialUnionFind {
	ll n;
	vl par, siz, pot;
	PotentialUnionFind(ll N) : par(N,-1) , siz(N,1) , pot(N,0){n=N;}
	// 根を求める
	ll root(ll x) {
		if (par[x] == -1) return x;
		ll tmp = root(par[x]);
		pot[x] += pot[par[x]];
		par[x] = tmp;
		return par[x];
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(ll x, ll y) {
		return root(x) == root(y);
	}
	//x よりいくつ大きい所に y があるか。根が一致しない場合は"0"
	ll potential(ll x,ll y){
		if(root(x) != root(y)) return 0;
		else return pot[y]-pot[x];
	}
	//x より w だけ大きい状態として y を併合。
	bool unite(ll x, ll y, ll w) {
		ll rx = root(x),ry = root(y);
		if (rx == ry) return false;
		w += pot[x]-pot[y];
		if (siz[rx] < siz[ry]) swap(rx, ry),w*=-1;
		par[ry] = rx;
		siz[rx] += siz[ry];
		siz[ry] = 0;
		pot[ry] = w;
		return true;
	}
	// x を含むグループのサイズ
	ll size(ll x) {
		return siz[root(x)];
	}
	//小さい順にUnionFindグラフを調整、O(n log n)
	void regulation(){
		vvl r(n);
		rep(i,n)r[root(i)].push_back(i);
		rep(i,n){
			if(r[i].size()==0)continue;
			ll mn = i;
			rep(j,r[i].size())if(pot[mn]>pot[r[i][j]])mn=r[i][j];
			siz[mn]=siz[i];
			siz[i]=0;
			ll tmp = pot[mn];
			rep(j,r[i].size()){
				pot[r[i][j]]-=tmp;
				par[r[i][j]] = mn;
			}
			par[mn]=-1;
		}
	}
	void debug(){
		rep(i,n)cout<<setw(4)<<left<<par[i]<<" ";
		cout<<endl;
		rep(i,n)cout<<setw(4)<<left<<pot[i]<<" ";
		cout<<endl;
	}
};

//分離可能UnionFind、経路圧縮をしない。
struct CuttingFind{
	vector<int> par, siz;
	CuttingFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	//根x と 根y のグループを併合する(お互い根ではない時、falseで何もしない)
	bool unite(int x, int y) {
		if (issame(x,y) || par[x] != -1 || par[y] != -1) {
			cout<<"error"<<endl;
			return false;
		}
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	//根の側から、その直系の子供を分離する。片方が根でもう片方が直系の子でなければならない。
	bool separate(int x,int y){
		if(par[y]==-1)swap(x,y);
		if(par[y]!=x||par[x]!=-1){
			cout<<"error2"<<endl;
			return false;
		}
		siz[x] -= siz[y];
		par[y]=-1;
		return true;
	}
	// x を含むグループのサイズを求める
	int size(int x) {
		return siz[root(x)];
	}
};
//セグ木,乗せる値の型が必要
template<typename T>
struct SegTree{
	ll size;
	ll tall;
	vector<T> data;
	function<T(T,T)> p;
	//セグ木に乗せる値の初期値をa配列にし、putの関数をセグ木に乗せる、dをデフォルト値に。
	SegTree(vector<T> a,function<T(T,T)> put,T d) : data(power(2,logax(2,a.size())+1)) {
		size = data.size()/2;
		tall=logax(2,size)+1;
		p=put;
		ll tmp=size;
		data = vector<T>(size*2,d);
		while(tmp!=0){
			if(tmp==size)rep(i,a.size())data[tmp+i]=a[i];
			else rep(i,tmp) data[tmp+i]=p(data[2*(tmp+i)],data[2*(tmp+i)+1]);
			tmp/=2;
		}
	}
	//更新、t番目の値をxにする。
	void update(ll t,T x){
		t+=size;
		while(t!=0){
			if(t>=size)data[t]=x;
			else data[t]=p(data[2*t],data[2*t+1]);
			t/=2;
		}
	}
	//取得、l~r区間内の評価値を取得する。
	T get(ll l,ll r){
		//lとrが範囲外なら範囲内に正す
		l=max(0LL,l);
		r=min(r,size-1);
		r++;
		T ans=data[0];
		ll pos=l+size;
		ll wid=1;
		//出来る限り上に上げきる。
		while(l+(wid*2)<=r){
			while(l%(wid*2)==0&&l+(wid*2)<=r)pos/=2,wid*=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+wid>r)pos*=2,wid/=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		return ans;
	}
	//セグ木デバッグ用、丸ごと出力
	void print(){
		rep(i,size)cout<<setw(7)<<left<<i;
		cout<<endl;
		ll pos=size;
		rep(i,tall){
			rep(j,size){
				if(j%power(2,i)==0)cout<<setw(7)<<left<<data[pos],pos++;
				else cout<<"       ";
			}
			pos/=4;
			cout<<endl;
		}
	}
};

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//乱数、ファイル入出力
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//17:28
//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vector<char> cc(n);
	rep(i,n)cin>>cc[i];
	vector<pair<char,ll>> c;
	c.push_back({cc[0],0});
	ll ans=n;
	rep(i,n){
		if(c.size()!=0&&cc[i]==c.back().first)c.back().second++;
		else c.push_back({cc[i],1});
		if(c.back().second==m)c.pop_back(),ans-=m;
	}

	cout<<ans<<endl;
	return 0;
}
