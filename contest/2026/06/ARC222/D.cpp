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

ll digitsum(ll n){
	string s=to_string(n);
	ll ans=0;
	rep(i,s.size()){
		ans+=s[i]-'0';
	}
	return ans;
}

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n),b(n);
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];
	ll ten=1000000000;

	unordered_map<ll,pair<ll,ll>>dp;
	dp[0]={0,inf};
	//[i]=下9桁がiで下9桁以外の桁和{最小値、繰り上がった場合の最小値}
	rep(i,n){
		unordered_map<ll,pair<ll,ll>>ndp;
		ll mn=inf;
		for(const auto vals:dp){
			ll now=vals.first;
			now*=10;
			//a
			{
				ll tmp=now+a[i];
				ll suteru=tmp/ten;
				tmp%=ten;
				pair<ll,ll> ans;
				if(suteru==10){
					ans.second=inf;
					//繰り上がった先でさらに繰り上がる場合,繰り上がっても何も起きない場合
					ans.first=min(vals.second.second,vals.second.first+1);
				}else if(suteru==9){
					//繰り上がらなかったが9の場合
					
					//新たに9を生やす遷移,9を追加するだけの遷移
					ans.second=min(vals.second.first+1,vals.second.second);

					//そもそも後で繰り上がらない場合
					ans.first=vals.second.first+9;
				}else {
					//完全に繰り上がらない場合
					ans={vals.second.first+suteru,inf};
				}
				if(ndp.count(tmp)){
					ndp[tmp].first=min(ndp[tmp].first,ans.first);
					ndp[tmp].second=min(ndp[tmp].second,ans.second);
				}else{
					ndp[tmp]=ans;
				}
				mn=min(mn,ndp[tmp].first+digitsum(tmp));
			}
			//b
			{
				ll tmp=now+b[i];
				ll suteru=tmp/ten;
				tmp%=ten;
				pair<ll,ll> ans;
				if(suteru==10){
					ans.second=inf;
					//繰り上がった先でさらに繰り上がる場合,繰り上がっても何も起きない場合
					ans.first=min(vals.second.second,vals.second.first+1);
				}else if(suteru==9){
					//繰り上がらなかったが9の場合
					
					//新たに9を生やす遷移,9を追加するだけの遷移
					ans.second=min(vals.second.first+1,vals.second.second);

					//そもそも後で繰り上がらない場合
					ans.first=vals.second.first+9;
				}else {
					//完全に繰り上がらない場合
					ans={vals.second.first+suteru,inf};
				}
				if(ndp.count(tmp)){
					ndp[tmp].first=min(ndp[tmp].first,ans.first);
					ndp[tmp].second=min(ndp[tmp].second,ans.second);
				}else{
					ndp[tmp]=ans;
				}
				mn=min(mn,ndp[tmp].first+digitsum(tmp));
			}
		}
		cout<<mn<<" ";
		swap(dp,ndp);
	}
	cout<<endl;
	return 0;
}
