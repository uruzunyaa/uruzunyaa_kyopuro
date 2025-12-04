//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 1e9
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



ll solve(){
	ll h,w;
	cin>>h>>w;
	if(h==0){return 1;}
	string a,b;
	cin>>a>>b;
	
	vector<string> ans(h,string(w,'?'));

	//中を埋める
	loop(i,1,h-2)loop(j,1,w-2){
		if((i+j)%2==0)ans[i][j]='+';
		else ans[i][j]='-';
	}

	if(a[0]=='1'&&b[b.size()-1]=='1'){
		cout<<"No"<<endl;
		return 0;
	}

	if(a[a.size()-1]=='1'&&b[0]=='1'){
		cout<<"No"<<endl;
		return 0;
	}

	if(a[0]=='0'&&b[0]=='0'){
		ans[0][0]='-';
		if(a[a.size()-1]=='0')ans[a.size()-1][0]='-';
		if(b[b.size()-1]=='0')ans[0][b.size()-1]='-';
	}

	if(a[a.size()-1]=='0'&&b[b.size()-1]=='0'){
		ans[a.size()-1][b.size()-1]='+';
		if(a[0]=='0')ans[0][b.size()-1]='+';
		if(b[0]=='0')ans[a.size()-1][0]='+';
	}

	rep(i,h){
		if(a[i]=='1'){
			ans[i][0]='+';
			ans[i][w-1]='-';
		}
	}

	rep(i,w){
		if(b[i]=='1'){
			ans[0][i]='+';
			ans[h-1][i]='-';
		}
	}

	if(a[0]=='1'){
		ll plus=0;
		rep(i,w){
			if(ans[0][i]=='+')plus++;
		}
		plus=(w/2)-plus;
		rep(i,w){
			if(ans[0][i]=='?'){
				if(plus>0){
					ans[0][i]='+';
					plus--;
				}else{
					ans[0][i]='-';
				}
			}
		}
	}

	if(a[h-1]=='1'){
		ll plus=0;
		rep(i,w){
			if(ans[h-1][i]=='+')plus++;
		}
		plus=(w/2)-plus;
		rep(i,w){
			if(ans[h-1][i]=='?'){
				if(plus>0){
					ans[h-1][i]='+';
					plus--;
				}else{
					ans[h-1][i]='-';
				}
			}
		}
	}

	if(b[0]=='1'){
		ll plus=0;
		rep(i,h){
			if(ans[i][0]=='+')plus++;
		}
		plus=(h/2)-plus;
		rep(i,h){
			if(ans[i][0]=='?'){
				if(plus>0){
					ans[i][0]='+';
					plus--;
				}else{
					ans[i][0]='-';
				}
			}
		}
	}

	if(b[w-1]=='1'){
		ll plus=0;
		rep(i,h){
			if(ans[i][w-1]=='+')plus++;
		}
		plus=(h/2)-plus;
		rep(i,h){
			if(ans[i][w-1]=='?'){
				if(plus>0){
					ans[i][w-1]='+';
					plus--;
				}else{
					ans[i][w-1]='-';
				}
			}
		}
	}

	//まだ決まってない奴は適当に埋める
	rep(i,h)rep(j,w)if(ans[i][j]=='?'){
		if(i==0||j==0)ans[i][j]='-';
		else ans[i][j]='+';
	}
	
	//正誤判定
	rep(i,h){
		bool f=true;
		ll syouki=0;
		rep(j,w){
			if(ans[i][j]=='+')syouki++;
			else syouki--;
			if(syouki<0)f=false;
		}
		if(syouki!=0)f=false;
		if((f&&a[i]=='1')||(!f&&a[i]=='0')){
			continue;	
		}
		cout<<"No"<<endl;
		return 0;
	}

	//正誤判定
	rep(i,w){
		bool f=true;
		ll syouki=0;
		rep(j,h){
			if(ans[j][i]=='+')syouki++;
			else syouki--;
			if(syouki<0)f=false;
		}
		if(syouki!=0)f=false;
		if((f&&b[i]=='1')||(!f&&b[i]=='0')){
			continue;	
		}
		cout<<"No"<<endl;
		return 0;
	}

	cout<<"Yes"<<endl;
	rep(i,h)cout<<ans[i]<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
