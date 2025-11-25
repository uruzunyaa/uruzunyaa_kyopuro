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
	string s;
	cin>>s;
	vector<pair<ll,char>> bk(26);
	rep(i,26)bk[i].second='a'+i;
	rep(i,s.size()){
		bk[s[i]-'a'].first++;
	}
	sort(bk.begin(),bk.end());
	ll n=s.size();
	
	if(bk.back().first<=(n+1)/2){
		//0に出来る場合
		string ans(n,'.');
		ll cnt=0;
		rrep(i,26){
			char mozi=bk[i].second;
			rep(j,bk[i].first){
				ans[cnt]=mozi;
				cnt+=2;
				if(cnt>=n)cnt=1;
			}
		}
		cout<<ans<<endl;
		return;
	}
	string ans(n,'.');
	rep(i,(n+1)/2){
		char mozi=bk[25].second;
		ans[i*2]=mozi;
	}
	bk[25].first-=(n+1)/2;
		
	n-=(n+1)/2;

	queue<char> a,b;
	rep(i,25){
		rep(j,bk[i].first)b.push(bk[i].second);
	}
	rep(j,bk[25].first)a.push(bk[25].second);


	ll blockcnt=b.size()+1;
	vl blocksiz(blockcnt);
	rep(i,blockcnt){
		blocksiz[i]=a.size()/blockcnt;
	}
	rep(i,a.size()%blockcnt){
		blocksiz[blockcnt-i-1]++;
	}
	

	ll index=1;
	rep(i,blockcnt-1){
		rep(j,blocksiz[i]){
			ans[index]=a.front();
			a.pop();
			index+=2;
		}
		ans[index]=b.front();
		b.pop();
		index+=2;
	}
	rep(j,blocksiz.back()){
		ans[index]=a.front();
		a.pop();
		index+=2;
	}
	

	cout<<ans<<endl;
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
