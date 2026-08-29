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

//二次元累積和を生成する。
struct Sums2d{
	ll h,w;
	vvl sums;
	Sums2d(vvl row){
		h=(row.size());
		w=(row[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row[i][j];
		}
	}
	Sums2d(vector<string> row_s){
		h=(row_s.size());
		w=(row_s[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row_s[i][j]-'0';
		}
	}
	//左上座標と右下座標を指定する。(半開区間でない)
	ll get(ll u,ll l,ll d,ll r){
		if(d<u||r<l)return 0;
		d++,r++;
		ll ans=0;
		ans+=sums[u][l];
		ans+=sums[d][r];
		ans-=sums[u][r];
		ans-=sums[d][l];
		return ans;
	}
};

//メイン
int main(){
	ll h,w,k;
	cin>>h>>w>>k;
	vector<string> s(h);
	rep(i,h)cin>>s[i];
	ll ans=0;
	Sums2d sums(s);
	vl mp(h*w+1,0);
	rep(d,h)rep(u,d+1){
		mp[0]++;
		rep(r,w){
			ll tmp=sums.get(u,0,d,r);
			if(tmp>=k)ans+=mp[tmp-k];
			mp[tmp]++;
		}
		rep(r,w){
			ll tmp=sums.get(u,0,d,r);
			mp[tmp]--;
		}
		mp[0]--;
	}
	cout<<ans<<endl;
	return 0;
}
