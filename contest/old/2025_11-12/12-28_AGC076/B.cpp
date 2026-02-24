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

vl goal;
ll cnt0;

vl execute(vl now,string s){
	vl a,b;
	ll n=now.size();
	rep(j,n){
		if(s[j]=='A')a.push_back(j);
		else b.push_back(j);
	}
	vl ra=a,rb=b;
	reverse(ra.begin(),ra.end());
	reverse(rb.begin(),rb.end());

	vl news(n);
	rep(j,a.size()){
		news[a[j]]=now[ra[j]];
	}
	rep(j,b.size()){
		news[b[j]]=now[rb[j]];
	}
	return news;
}

string check(vl x){
	ll n=x.size();
	bool f=true;
	ll over=0;
	string ans(n,'B');
	rep(i,cnt0){
		if(x[i]==0){
			f=false;
			ans[i]='A';
		}
		if(f&&x[i]==1){
			ans[i]='A';
			over++;
		}
	}
	loop(i,cnt0,n-1){
		if(over==0)break;
		if(x[i]==0){
			ans[i]='A';
			over--;
		}
	}

	if(execute(x,ans)==goal)return ans;
	else return string();
}

string revcheck(vl x){
	ll n=x.size();

	bool f=true;
	ll over=0;
	string ans(n,'B');
	rep(i,cnt0){
		if(x[i]==0){
			f=false;
			ans[i]='A';
		}
		if(f&&x[i]==1){
			ans[i]='A';
			over++;
		}
	}
	loop(i,cnt0,n-1){
		if(over==0)break;
		if(x[i]==0){
			ans[i]='A';
			over--;
		}
	}

	return ans;
}

void solve(){
	ll n;
	cin>>n;
	vl x(n);
	rep(i,n)cin>>x[i];
	goal=x;
	sort(goal.begin(),goal.end());

	cnt0=0;
	rep(i,n)if(x[i]==0)cnt0++;

	if(goal==x){
		cout<<0<<endl;
		return;
	}

	vector<string> fans1,fans2;

	vl bk=x;
	while(1){
		if(x==goal)break;
		rep(i,n)x[i]^=1;
		fans1.push_back(revcheck(x));
		x=execute(x,fans1.back());
	}
	x=bk;
	rep(i,n)x[i]^=1;
	while(1){
		rep(i,n)x[i]^=1;
		if(x==goal)break;
		fans2.push_back(revcheck(x));
		x=execute(x,fans2.back());
	}
	if(fans1.size()<fans2.size()){
		cout<<fans1.size()<<endl;
		rep(i,fans1.size())cout<<fans1[i]<<endl;
	}else{
		cout<<fans2.size()<<endl;
		rep(i,fans2.size())cout<<fans2[i]<<endl;
	}
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
