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
#include<atcoder/lazysegtree>


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

//powerとlogが前提条件
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
};


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

ll sm(ll a,ll b){
	return a+b;
}

using S = long long;
using F = long long;

const S INF = 8e18;

S op(S a, S b){ return std::max(a, b); }
S e(){ return -INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }


//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl a(n),l(n),r(n),home(n);
	rep(i,n){
		home[i]=i;
		cin>>a[i]>>l[i]>>r[i];
		l[i]--,r[i]--;
	}
	vl tmp=a;
	rep(i,m-n)tmp.push_back(0);
	SegTree<ll> seg(tmp,sm,0);
	std::vector<S> v(m,0);
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> lzseg(v);

	ll ans=0;
	rep(i,n){
		ans+=a[i]*(r[i]-l[i]+1);
		ans-=seg.get(l[i],r[i]);
		lzseg.apply(l[i],r[i]+1,1);
	}

	//cout<<ans<<endl;

	ll q;
	cin>>q;
	while(q--){
		ll x,y,nl,nr;
		cin>>x>>y>>nl>>nr;
		x--,y--,nl--,nr--;

		//影響範囲から覗いておく
		lzseg.apply(l[x],r[x]+1,-1);

		//元の物を減算
		ans-=a[x]*(r[x]-l[x]+1);
		ans+=seg.get(l[x],r[x]);
		ans+=lzseg.get(home[x])*a[x];
		

		//更新
		seg.update(home[x],0);
		home[x]=y;
		seg.update(home[x],a[x]);
		
		
		l[x]=nl;
		r[x]=nr;
		
		

		//再度加算
		ans+=a[x]*(r[x]-l[x]+1);
		ans-=seg.get(l[x],r[x]);
		ans-=lzseg.get(home[x])*a[x];

		lzseg.apply(l[x],r[x]+1,1);

		cout<<ans<<endl;
	}
	
	return 0;
}
