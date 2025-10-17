#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
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
//底がaの対数xを計算。ただし小数点は繰り上げ。
ll logax(ll a, ll x){
	ll result = 0;
	ll power = 1;
	while (power < x){
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
ifstream fin("./DefaultFile");
ofstream fout("./DefaultOutFile");//出力する場合の出力先を指定



// Binary Indexed Tree (1.1 基本実装)
// 1-based indexing
class BIT
{
public:

	BIT() = default;

	// 長さ size の数列で初期化
	explicit BIT(size_t size)
		: m_bit(size + 1) {}

	// 数列で初期化
	explicit BIT(const std::vector<long long>& v)
		: BIT(v.size())
	{
		for (int i = 0; i < v.size(); ++i)
		{
			add((i + 1), v[i]);
		}
	}

	// 閉区間 [1, r] の合計を返す (1-based indexing)
	long long sum(int r) const
	{
		long long ret = 0;

		for (; 0 < r; r -= (r & -r))
		{
			ret += m_bit[r];
		}

		return ret;
	}

	// 閉区間 [l, r] の合計を返す (1-based indexing)
	long long sum(int l, int r) const
	{
		return (sum(r) - sum(l - 1));
	}

	// 数列の i 番目の要素を加算 (1-based indexing)
	void add(int i, long long value)
	{
		for (; i < m_bit.size(); i += (i & -i))
		{
			m_bit[i] += value;
		}
	}

private:

	std::vector<long long> m_bit;
};
ll tento_number(vl A){
	ll N=A.size();
	BIT bit(N);
	long long answer = 0;
	for (int i = 0; i < N; ++i)
	{
		answer += bit.sum(A[i], N);
		bit.add(A[i], 1);
	}
	return answer;

}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(z,t){
		ll n;
		cin>>n;
		vl p(n);
		rep(i,n)cin>>p[i];

		set<ll> m;
		deque<ll> ans;
		m.insert(p[0]);
		ans.push_back(p[0]);
		auto it= m.begin();

		loop(i,1,n-1){
			if(*it<p[i]){
				ans.push_back(p[i]);
				m.insert(p[i]);
				if(i%2==0)it++;
			}else{
				ans.push_front(p[i]);
				m.insert(p[i]);
				if(i%2==1)it--;
			}
		}
		vl ans2;
		
		rep(i,n)ans2.push_back(ans.at(i));
		
		cout<<tento_number(ans2)<<endl;
		rep(i,n)cout<<ans2[i]<<" ";
		cout<<endl;
	}
	return 0;
}
