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


//メイン
int main(){
	ll xa,ya,xb,yb,n,m,l;
	cin>>xa>>ya>>xb>>yb>>n>>m>>l;
	if((xa+ya+xb+yb)%2==1){
		cout<<0<<endl;
		return 0;
	}
	map<char,ll>LRUD;
	LRUD['D']=0;
	LRUD['R']=1;
	LRUD['U']=2;
	LRUD['L']=3;

	vector<pair<ll,ll>> a(m),b(l);
	set<ll> st;
	ll time=0;
	rep(i,m){
		char c;
		ll num;
		cin>>c>>num;
		a[i]={LRUD[c],num};
		time+=num;
		st.insert(time);
	}
	time=0;
	rep(i,l){
		char c;
		ll num;
		cin>>c>>num;
		time+=num;
		b[i]={LRUD[c],num};
		st.insert(time);
	}
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());

	ll ans=0;

	ll zikoku=0;
	for(const auto & val:st){
		if(a.back().second==0)a.pop_back();
		if(b.back().second==0)b.pop_back();

		ll nagasa=val-zikoku;
		
		ll dist=abs(xa-xb)+abs(ya-yb);
		dist/=2;
		if(dist==0){
			if(a.back().first==b.back().first)ans+=nagasa;
		}else if(nagasa>=dist){
			ll x1=xa+dx[a.back().first]*dist;
			ll y1=ya+dy[a.back().first]*dist;
			ll x2=xb+dx[b.back().first]*dist;
			ll y2=yb+dy[b.back().first]*dist;
			if(x1==x2&&y1==y2)ans++;

		}

		xa+=dx[a.back().first]*nagasa;
		ya+=dy[a.back().first]*nagasa;
		xb+=dx[b.back().first]*nagasa;
		yb+=dy[b.back().first]*nagasa;
		a.back().second-=nagasa;
		b.back().second-=nagasa;
		zikoku=val;

		//cout<<"Nはいくつかというと:"<<ans<<endl;
	}
	cout<<ans<<endl;
	return 0;
}
