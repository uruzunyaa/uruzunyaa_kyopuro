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

vvl moved(vector<string> s,bool tate,bool yoko){
	if(tate){
		reverse(s.begin(),s.end());
	}
	if(yoko){
		rep(i,s.size()){
			reverse(s[i].begin(),s[i].end());
		}
	}
	ll h=s.size();
	ll w=s[0].size();
	vvl ans(h,vl(w,0));
	ans[0][0]=1;
	rep(i,h)rep(j,w){
		if(s[i][j]=='#')continue;
		//上から
		if(i!=0)ans[i][j]+=ans[i-1][j];

		//左から
		if(j!=0)ans[i][j]+=ans[i][j-1];

		ans[i][j]%=mod;
	}
	if(tate){
		reverse(ans.begin(),ans.end());
	}
	if(yoko){
		rep(i,ans.size()){
			reverse(ans[i].begin(),ans[i].end());
		}
	}
	return ans;
}

ll solve(){
	ll h,w;
	cin>>h>>w;
	if(h==0)return 1;
	vector<string> s(h);
	rep(i,h)cin>>s[i];


	// if(h%2==0){
	// 	string t;
	// 	t.push_back('.');
	// 	loop(i,1,w-2)t.push_back('#');
	// 	t.push_back('.');
	// 	s.push_back(t);
	// 	reverse(s.begin(),s.end());
	// 	h++;
	// }

	
	ll mid=h/2;

	vvl siromae=moved(s,false,false);
	vl sirousiro=moved(s,true,true)[mid];
	vvl kuromae=moved(s,true,false);
	vl kurousiro=moved(s,false,true)[mid];

	ll ans=siromae[h-1][w-1]*kuromae[0][w-1];
	ans%=mod;

	//初めてここで衝突を引く
	rep(i,w){
		if(s[mid][i]=='#')continue;
		ll tmp=0;

		ll usiro=sirousiro[i]*kurousiro[i];
		usiro%=mod;

		ll mae=siromae[mid][i]*kuromae[mid][i];
		mae%=mod;

		tmp+=mae*usiro;
		tmp%=mod;

		if(i!=0){
			ll kazoetamae=siromae[mid][i-1]*kuromae[mid][i-1];
			kazoetamae%=mod;

			ll kazoeta=kazoetamae*usiro;
			kazoeta%=mod;

			tmp+=mod-kazoeta;
			tmp%=mod;
		}

		tmp%=mod;
		ans+=mod-tmp;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
