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
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

//約数列挙
vl get_divisor(ll n){
	vl ans;
	for(ll i=1;i*i<=n;i++){
		if(n%i!=0)continue;
		ans.push_back(i);
		if(i*i!=n)ans.push_back(n/i);
	}
	sort(ans.begin(),ans.end());
	return ans;
}


int main(){
	ll n,m,w;
	cin>>n>>m>>w;
	vl tmp=get_divisor(w);

	for(auto val:tmp){
		ll nanshu=val;
		if(m%nanshu!=0)continue;
		ll kosu=m/nanshu;
		if(w%nanshu!=0)continue;
		ll sums=w/nanshu;
		if(kosu>n)continue;

		ll mn=(1+kosu)*kosu;
		mn/=2;
		ll mx=((n-kosu+2)+n)*(kosu-1);
		mx/=2;
		mx++;

		if(mn>sums||mx<sums)continue;

		ll migi=n-kosu;
		vl ans(kosu);
		rep(i,kosu)ans[i]=i+1;
		ll nokori=sums-mn;
		rrep(i,kosu){
			if(nokori>migi){
				ans[i]+=migi;
				nokori-=migi;
			}else{
				ans[i]+=nokori;
				break;
			}
		}

		vl fans(n);
		rep(i,n)fans[i]=i;
		rep(i,ans.size()){
			ans[i]--;
		}
		rep(i,ans.size()){
			fans[ans[i]]=ans[(i+1)%ans.size()];
		}
		rep(i,n)fans[i]++;
		vdbg(fans);
		return 0;
	}
	cout<<-1<<endl;
	return 0;
}
