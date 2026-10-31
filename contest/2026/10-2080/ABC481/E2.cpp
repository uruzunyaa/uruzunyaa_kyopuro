//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
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

class Point{
public:
	ll x,y;
	bool check=false;
	//Point(){}
	//Point(ll x, ll y):x(x),y(y){}
};

//aの方が小さいか。
bool check(Point a, Point b){
	
	if(b.check)return false;
	if(a.check)return true;

	if(a.x*b.x<0){
		return a.x>0;
	}else if(a.x*b.x==0){
		if(a.x==0&&b.x==0){
			return (a.y>0&&b.y<0);
		}else if(a.x==0){
			if(a.y>0)return true;
			if(b.x<0)return true;
			return false;
		}else {
			if(b.y>0)return false;
			if(a.x<0)return false;
			return true;
		}
	}
	//象限が同じ場合
	return a.y*b.x>a.x*b.y;
}

//https://atcoder.jp/contests/abc442/submissions/72733216

void solve(){
	ll n;
	cin>>n;
	vector<Point> p;
	vl a(n),b(n);
	rep(i,n){
		cin>>a[i]>>b[i];
		p.push_back({a[i],b[i]});
	}
	sort(p.begin(),p.end(),check);
	
	ll l=0;
	ll ans=0;
	bool f=true;
	rep(r,n){
		if(p[r].x>=0){
			continue;
		}
		f=false;
		//左がダメになるまで進める
		Point gyaku={-p[r].x,-p[r].y};

		while(check(p[l],gyaku)){
			l++;
		}
		ll cnt=r-l+1;
		ans=max(ans,cnt);
		ans=max(ans,n-cnt+1);
	}
	if(f){
		cout<<n<<endl;
		return;
	}
	cout<<ans<<endl;
	
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();

	return 0;
}
