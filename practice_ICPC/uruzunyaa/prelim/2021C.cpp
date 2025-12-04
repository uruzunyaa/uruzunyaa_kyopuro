//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
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

vvl g;
string s;

vector<map<ll,pair<ll,ll>>> dp;

pair<ll,ll> dfs(ll node,ll before){
	if(dp[node].count(before))return dp[node][before];
	if(s[node]!='+'&&s[node]!='-'){
		dp[node][before]={s[node]-'0',s[node]-'0'};
		return dp[node][before];
	}

	pair<ll,ll> ans={-inf,inf};
	vector<pair<ll,ll>> list;
	rep(i,g[node].size()){
		if(g[node][i]==before)continue;
		list.push_back(dfs(g[node][i],node));
	}
	sort(list.begin(),list.end());

	do{
		pair<ll,ll> tmp=list[0];
		loop(i,1,list.size()-1){
			if(s[node]=='+'){
				tmp.first+=list[i].first;
				tmp.second+=list[i].second;
			}else{
				tmp.first-=list[i].second;
				tmp.second-=list[i].first;
			}
		}
		ans.first=max(ans.first,tmp.first);
		ans.second=min(ans.second,tmp.second);
	}while(next_permutation(list.begin(),list.end()));
	dp[node][before]=ans;
	return dp[node][before];
}

ll solve(){
	cin>>s;
	if(s=="-1"){return 1;}
	g=vvl(s.size());
	dp=vector<map<ll,pair<ll,ll>>>(s.size());

	vl st;
	rep(i,s.size()){
		st.push_back(i);
		if(s[i]==')'){
			ll par=st[st.size()-3];
			ll chil1=st[st.size()-2];
			ll chil2=st[st.size()-4];
			g[par].push_back(chil1);
			g[par].push_back(chil2);
			g[chil1].push_back(par);
			g[chil2].push_back(par);
			st.pop_back();
			st.pop_back();
			st.pop_back();
			st.pop_back();
			st.pop_back();
			st.push_back(par);
		}
	}
	ll par=st[st.size()-4];
	ll chil1=st[st.size()-1];
	ll chil2=st[st.size()-3];
	ll chil3=st[st.size()-5];
	g[par].push_back(chil1);
	g[par].push_back(chil2);
	g[par].push_back(chil3);
	g[chil1].push_back(par);
	g[chil2].push_back(par);
	g[chil3].push_back(par);

	ll ans=-inf;
	rep(i,s.size()){
		if(g[i].size()==3){
			ans=max(ans,dfs(i,-1).first);
		}
	}
	cout<<ans<<endl;

	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
