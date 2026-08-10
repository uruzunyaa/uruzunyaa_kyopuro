//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
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
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
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


//メイン
int main(){
	ll n,l;
	cin>>n>>l;
	vl a(n);
	rep(i,n)cin>>a[i];

	vector<vector<vector<double>>> dp(n+1,vector<vector<double>>(n+1,vector<double>(l+1,0)));
	//dp[i][j][d]=i個みっけた、j個知ってる、ダメージd
	dp[0][0][0]=1;

	rep(i,n)rep(j,n-i+1)rep(d,l){
		//知らんカードの数
		ll kouho=2*n-2*i-j;
		//知ってるのとマッチする確率
		double match=((double)j)/((double)kouho);
		
		//マッチした時
		if(j!=0)dp[i+1][j-1][d]+=match*dp[i][j][d];
		
		if(kouho==1)continue;
		if(i+j==n)continue;

		//マッチしなかったとき
		match=1-match;
		//次がピッタリマッチする場合
		double one=match*(((double)1)/(double)(kouho-1));
		dp[i+1][j][d]+=dp[i][j][d]*one;
		if(kouho==2)continue;

		if(d==l-1){
			dp[i][j][l]+=dp[i][j][d]*(match-one);
			continue;
		}

		//2個目のマッチ確率
		double two=match*((double)(j))/((double)(kouho-1));
		double twono=match-two-one;
		//2個目がマッチする場合
		dp[i+1][j][d+1]+=two*dp[i][j][d];
		
		if(i+j+2>n)continue;

		//2個目もマッチしない場合
		dp[i][j+2][d+1]+=twono*dp[i][j][d];
	}

	rep(i,l)dp[n][0][l]+=dp[n][0][i];

	vector<double> cnts(n+1,0);
	rep(i,n+1)rep(j,n+1){
		cnts[i]+=dp[i][j][l];
	}

	double ans=0;
	rep(i,n+1){
		double kakuritu=((double)i)/((double)n);
		rep(k,n){
			ans+=cnts[i]*kakuritu*a[k];
		}
	}
	cout<<fixed<<setprecision(15)<<ans<<endl;
	return 0;
}
