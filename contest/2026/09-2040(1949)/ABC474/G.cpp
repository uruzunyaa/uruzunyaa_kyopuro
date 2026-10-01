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

void solve(){
	ll n,k;
	cin>>n>>k;
	if(k<n-1){
		cout<<"No"<<endl;
		return;
	}
	if(n%2==0){
		cout<<"No"<<endl;
		return;
	}
	if(k>(n*n-1)/2){
		cout<<"No"<<endl;
		return;
	}

	//多分
	if(k%2==1){
		cout<<"No"<<endl;
		return;
	}
	k-=n-1;

	vvl visit(n,vl(n,0));
	string ans;
	visit[0][0]=1;
	ll x=0,y=0;
	while(k>0){
		while(x<n-1&&k>0){
			x++;
			ans.push_back('R');
			visit[x][y]=1;
			k--;
		}
		y++;
		ans.push_back('D');
		visit[x][y]=1;
		while(x!=0){
			x--;
			ans.push_back('L');
			visit[x][y]=1;
		}
		y++;
		ans.push_back('D');
		visit[x][y]=1;
	}

	//まず下がる
	while(y<n-1){
		y++;
		ans.push_back('D');
		visit[x][y]=1;
	}

	//ここからは増やさないように
	while(x<n-1||y<n-1){
		//右
		x++;
		ans.push_back('R');
		visit[x][y]=1;
		//上がる
		while(y>0){
			if(visit[x][y-1])break;
			y--;
			ans.push_back('U');
			visit[x][y]=1;
		}
		//右
		x++;
		ans.push_back('R');
		visit[x][y]=1;
		//下がる
		while(y<n-1){
			y++;
			ans.push_back('D');
			visit[x][y]=1;
		}
	}
	cout<<"Yes"<<endl;
	cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
