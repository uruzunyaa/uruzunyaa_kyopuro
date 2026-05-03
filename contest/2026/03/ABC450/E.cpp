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
#define inf 1000000000000000000LL
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

map<ll,ll> mp;
vvl cnt;
string x,y;
vvl nokori;

vl solve(ll r){
	vl ans(26,0);
	while(r>y.size()){
		auto it=mp.upper_bound(r);
		it--;
		ll ind=it->second;
		
		r-=it->first;

		rep(j,26)ans[j]+=cnt[ind][j];
	}

	rep(j,26){
		ans[j]+=nokori[r][j];
	}

	return ans;
}

//メイン
int main(){
	cin>>x>>y;
	x=y+x;
	swap(x,y);

	vl xsum(26,0),ysum(26,0);

	nokori.push_back(ysum);
	rep(i,y.size()){
		ll ind=y[i]-'a';
		ysum[ind]++;
		nokori.push_back(ysum);
	}

	cnt.push_back(xsum);
	cnt.push_back(ysum);

	mp[y.size()]=1;
	loop(i,2,inf){
		ll sums=0;
		vl tmp(26,0);
		rep(j,26)tmp[j]+=cnt[i-1][j]+cnt[i-2][j],sums+=tmp[j];
		cnt.push_back(tmp);
		mp[sums]=i;
		if(sums>inf){
			break;
		}
	}

	ll q;
	cin>>q;

	while(q--){
		ll l,r;
		char c;
		cin>>l>>r>>c;
		l--;
		
		ll ind=c-'a';

		vl ans=solve(r);
		vl tmp=solve(l);
		cout<<ans[ind]-tmp[ind]<<endl;
	}
	return 0;
}
