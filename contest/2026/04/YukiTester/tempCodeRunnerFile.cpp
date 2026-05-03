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

void two(){
	ll n,m;
	cin>>n>>m;
	vl bk(m+1,0);
	vl aite(m+1,0);
	rep(i,n){
		ll c;
		cin>>c;
		bk[c]++;
	}
	map<ll,ll> mp;

	loop(i,1,m-1){
		string turn,res;
		ll type,cnt;
		
		cin>>turn;
		cin>>res;
		cin>>type>>cnt;
		mp[type]=cnt;
		aite[i]=type-1;

		cin>>turn;
		cout<<"ASK "<<bk[i]+1<<endl;
		cin>>res;
		cin>>type>>cnt;
		mp[type]=cnt;

	}

	bool guessed=false;

	while(1){
		string turn,res;
		cin>>turn;
		if(turn=="TURN"){
			ll mex=m;
			loop(i,1,m-1){
				if(mp.count(i))continue;
				mex=i;
				break;
			}
			if(mex==m)break;
			cout<<"ASK "<<mex<<endl;
		}
		cin>>res;
		ll type,cnt;
		cin>>type>>cnt;

		if(res=="GUESSED"){
			guessed=true;
			continue;
		}
		mp[type]=cnt;
	}

	vl ans;
	loop(i,1,m-1){
		ll cnt=mp[i]-bk[i]-aite[i];
		rep(z,cnt)ans.push_back(i);
	}
	while(ans.size()<n)ans.push_back(m);
	cout<<"GUESS ";
	vdbg(ans);

	string tmp;
	rep(i,5)cin>>tmp;
	if(guessed)rep(i,4)cin>>tmp;
}

void one(){
	ll n,m;
	cin>>n>>m;
	vl bk(m+1,0);
	vl aite(m+1,0);
	rep(i,n){
		ll c;
		cin>>c;
		bk[c]++;
	}
	map<ll,ll> mp;

	loop(i,1,m-1){
		string turn,res;
		cin>>turn;
		cout<<"ASK "<<bk[i]+1<<endl;
		cin>>res;
		ll type,cnt;
		cin>>type>>cnt;
		mp[type]=cnt;

		cin>>turn;
		cin>>res;
		cin>>type>>cnt;
		mp[type]=cnt;
		aite[i]=type-1;
	}

	bool guessed=false;
	while(1){
		string turn,res;
		cin>>turn;
		if(turn=="TURN"){
			ll mex=m;
			loop(i,1,m-1){
				if(mp.count(i))continue;
				mex=i;
				break;
			}
			if(mex==m)break;
			cout<<"ASK "<<mex<<endl;
		}
		cin>>res;
		ll type,cnt;
		cin>>type>>cnt;

		if(res=="GUESSED"){
			guessed=true;
			continue;
		}
		mp[type]=cnt;
	}

	vl ans;
	loop(i,1,m-1){
		ll cnt=mp[i]-bk[i]-aite[i];
		// cout<<i<<" "<<cnt<<endl;
		// cout<<mp[i]<<" "<<bk[i]<<" "<<aite[i]<<endl;
		rep(z,cnt)ans.push_back(i);
	}
	while(ans.size()<n)ans.push_back(m);
	cout<<"GUESS ";
	vdbg(ans);

	string tmp;
	rep(i,5)cin>>tmp;
	if(guessed)rep(i,4)cin>>tmp;
}

//メイン
int main(){
	ll p;
	cin>>p;
	if(p==1)one();
	else two();
	
	return 0;
}
