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

void solve(){
	return;
}

string bubun(string s,char a,char b){
	string ans;
	rep(i,s.size()){
		if(s[i]==a||s[i]==b)ans.push_back(s[i]);
	}
	return ans;
}

ll shukicheck(string s){
	ll n=s.size();
	loop(i,1,n){
		bool f=true;
		if(n%i!=0)continue;
		rep(j,i){
			rep(k,n/i){
				if(s[j]!=s[j+k*i])f=false;
			}
		}
		if(f){
			return i;
		}
	}
	return n;
}

//メイン
int main(){
	ll n;
	string s;
	cin>>n>>s;

	ll ansnokori=n;
	loop(i,1,n){
		bool f=true;
		if(n%i!=0)continue;
		rep(j,i){
			rep(k,n/i){
				if(s[j]!=s[j+k*i])f=false;
			}
		}
		if(f){
			ansnokori=n/i;
			string ns;
			rep(j,i)ns.push_back(s[j]);
			s=ns;
			n=s.size();
		}
	}

	set<char> st;
	rep(i,n)st.insert(s[i]);

	string list;
	for(auto val:st)list.push_back(val);

	char a,b;
	rep(i,list.size())rep(j,i){
		string tmp=bubun(s,list[i],list[j]);
		if(shukicheck(tmp)==tmp.size()){
			a=list[i];
			b=list[j];
			break;
		}
	}

	cout<<ansnokori<<endl;
	cout<<1000*999<<endl;
	loop(i,1,999){
		rep(j,i)cout<<a;
		rep(j,i)cout<<b;
	}
	cout<<endl;
	return 0;
}
