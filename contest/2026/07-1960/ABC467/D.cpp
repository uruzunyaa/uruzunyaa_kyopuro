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

struct point {
    ll x,y;
};

// p1→p2 のベクトルに対して p3 が線上(0), 左(1), 右(2) のいずれかを返す
ll orientation(const point& a, const point& b, const point& c) {
    // 外積 (b−a)×(c−a)
    ll cross = (b.x - a.x) * (c.y - a.y)
                 - (b.y - a.y) * (c.x - a.x);
    if (cross == 0) return 0;      // ほぼゼロなら直線上
    return (cross > 0 ? 1 : 2);           // 正なら左(1)、負なら右(2)
}

void solve(){
	vl ps(8);
	rep(i,8)cin>>ps[i];
	ll a1dx=ps[0]-ps[2];
	ll a1dy=ps[3]-ps[1];
	ll a1g=gcd(a1dy,a1dx);
	a1dx/=a1g;
	a1dy/=a1g;
	if(a1dx<0){
		a1dx*=-1;
		a1dy*=-1;
	}
	
	ll a2dx=ps[4]-ps[6];
	ll a2dy=ps[7]-ps[5];
	ll a2g=gcd(a2dy,a2dx);
	a2dx/=a2g;
	a2dy/=a2g;
	if(a2dx<0){
		a2dx*=-1;
		a2dy*=-1;
	}
	
	if(a1dx!=a2dx||a1dy!=a2dy){
		cout<<"Yes"<<endl;
		return;
	}
	point a={ps[0],ps[3]};
	point b={ps[2],ps[1]};
	point c={ps[4],ps[7]};
	point d={ps[6],ps[5]};

	if(orientation(a,b,c)==0||orientation(a,b,d)==0)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return ;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
