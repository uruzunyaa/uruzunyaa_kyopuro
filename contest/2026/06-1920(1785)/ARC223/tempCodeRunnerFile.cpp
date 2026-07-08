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

void solve(){
	ll n,m;
	cin>>n>>m;
	vl a(n),b(m);
	rep(i,n)cin>>a[i];
	rep(i,m)cin>>b[i];

	if(a.front()!=b.front()||a.back()!=b.back()){
		cout<<"No"<<endl;
		return;
	}
	vl sa,sb;
	rep(i,n-1)sa.push_back(abs(a[i]-a[i+1]));
	rep(i,m-1)sb.push_back(abs(b[i]-b[i+1]));

	if(n%2!=m%2){
		cout<<"No"<<endl;
		return;
	}

	n--,m--;

	a=sa,b=sb;

	vl na,nb;
	{
		ll cnt=0;
		rep(i,n){
			if(a[i]==1)cnt++;
			else{
				na.push_back(cnt);
				cnt=0;
			}
		}
		na.push_back(cnt);
	}
	{
		ll cnt=0;
		rep(i,m){
			if(b[i]==1)cnt++;
			else{
				nb.push_back(cnt);
				cnt=0;
			}
		}
		nb.push_back(cnt);
	}
	
	if(na.size()!=nb.size()){
		cout<<"No"<<endl;
		return;
	}

	rep(i,na.size()){
		if(na[i]!=0)continue;
		if(na[i]==nb[i])continue;
		if(i!=0&&na[i-1]<nb[i-1]){
			na[i-1]++;
			na[i]++;
		}else if(i!=na.size()-1&&na[i+1]<nb[i+1]){
			na[i]++;
			na[i+1]++;
		}else{
			cout<<"No"<<endl;
			return;
		}
	}

	//隣合う加算、0じゃない場所に2加算が出来る
	rep(i,na.size()-1){
		if(na[i]>nb[i]){
			cout<<"No"<<endl;
			return;
		}
		ll tmp=nb[i]-na[i];
		tmp%=2;
		na[i]+=tmp;
		na[i+1]+=tmp;
	}
	if(na.back()>nb.back()){
		cout<<"No"<<endl;
		return;
	}

	cout<<"Yes"<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
