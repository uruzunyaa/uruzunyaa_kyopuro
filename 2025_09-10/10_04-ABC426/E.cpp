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

double dist(double tx,double ty,double ax,double ay){
	return (tx-ax)*(tx-ax)+(ty-ay)*(ty-ay);
}

void solve(){
	double tsx,tsy,tgx,tgy,asx,asy,agx,agy;
	cin>>tsx>>tsy>>tgx>>tgy>>asx>>asy>>agx>>agy;

	double tnorm=(tgx-tsx)*(tgx-tsx)+(tgy-tsy)*(tgy-tsy);
	double anorm=(agx-asx)*(agx-asx)+(agy-asy)*(agy-asy);

	tnorm=sqrt(tnorm);
	anorm=sqrt(anorm);
	

	if(tnorm>anorm){
		swap(tnorm,anorm);
		swap(tsx,asx);
		swap(tsy,asy);
		swap(tgx,agx);
		swap(tgy,agy);
	}
	
	double tdx=(tgx-tsx)/tnorm;
	double tdy=(tgy-tsy)/tnorm;
	double adx=(agx-asx)/anorm;
	double ady=(agy-asy)/anorm;


	double ans=dist(tsx,tsy,asx,asy);
	//double ans=inf;


	double mn=0,mx=tnorm;
	while(mx-mn>eps){
		double mid1=mn+mn+mx;
		mid1/=3;
		double mid2=mn+mx+mx;
		mid2/=3;

		double tkx1=tsx+tdx*mid1;
		double tky1=tsy+tdy*mid1;
		double akx1=asx+adx*mid1;
		double aky1=asy+ady*mid1;

		double tkx2=tsx+tdx*mid2;
		double tky2=tsy+tdy*mid2;
		double akx2=asx+adx*mid2;
		double aky2=asy+ady*mid2;

		double dist1=dist(tkx1,tky1,akx1,aky1);
		double dist2=dist(tkx2,tky2,akx2,aky2);

		if(dist1<dist2)mx=mid2;
		else mn=mid1;

		ans=min(ans,min(dist1,dist2));
	}

	//cout<<mn<<endl;

	mn=tnorm,mx=anorm;
	while(mx-mn>eps){
		double mid1=mn+mn+mx;
		mid1/=3;
		double mid2=mn+mx+mx;
		mid2/=3;

		double tkx1=tgx;
		double tky1=tgy;
		double akx1=asx+adx*mid1;
		double aky1=asy+ady*mid1;

		double tkx2=tgx;
		double tky2=tgy;
		double akx2=asx+adx*mid2;
		double aky2=asy+ady*mid2;

		double dist1=dist(tkx1,tky1,akx1,aky1);
		double dist2=dist(tkx2,tky2,akx2,aky2);

		if(dist1<dist2)mx=mid2;
		else mn=mid1;

		ans=min(ans,min(dist1,dist2));
	}

	cout<<fixed<<setprecision(15)<<sqrt(ans)<<endl;

}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
