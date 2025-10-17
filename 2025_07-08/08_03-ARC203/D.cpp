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


//メイン
int main(){
	ll n;
	cin>>n;
	
	ll cntone=0;
	vl a(n);
	rep(i,n)cin>>a[i],cntone+=a[i];

	//tzは2個以上の0の連続区間を持つ
	map<ll,ll> tz;

	ll ind=-inf;
	rep(i,n-1){
		if(ind==-inf&&a[i]==0&&a[i+1]==0){
			ind=i;
		}
		if(ind!=-inf&&a[i+1]==1){
			tz[ind]=i+1;
			ind=-inf;
		}
	}
	if(ind!=-inf)tz[ind]=n;

	for(const auto & val:tz){
		cout<<val.first<<" "<<val.second<<endl;
	}

	ll q;
	cin>>q;
	while(q--){
		ll c;
		cin>>c;
		c--;
		if(a[c]==0){
			a[c]=1;
			cntone++;
		}else{
			a[c]=0;
			cntone--;
		}
		if(cntone==n){
			cout<<n<<endl;
			continue;
		}

		if(a[c]==0){
			auto it = tz.upper_bound(c);
			ll right = -inf;
			if(it!=tz.end()){
				if(it->first == c+1){
					right=it->second;
				}
			}

			ll left = inf;
			if(it!=tz.begin()){
				it--;
				if(it->second == c){
					left=it->first;
				}
				it++;
			}
			
			if(right!=-inf)tz.erase(it);
			if(left!=inf)tz.erase(left);
			right = max(right,c+1);
			if(c!=n-1&&a[c+1]==0){
				right=max(right,c+2);
			}

			left=min(left,c);
			if(c!=0&&a[c-1]==0){
				left=min(left,c-1);
			}

			if(right-left != 1){
				tz[left] = right;
			}
		}else{
			auto it = tz.upper_bound(c);
			ll left = inf,right=inf;
			if(it!=tz.begin()){
				it--;
				left = it->first;
				right = it->second;
				tz.erase(it);
				if(c-left >= 2) tz[left]=c;
				if(right - (c+1) >= 2)tz[c+1]=right;
			}
		}
		ll ans = tz.size()*3-1;
		if(tz.size()==0){
			if(a[0]==0&&a[n-1]==0){
				cout<<3<<endl;
				continue;
			}else{
				cout<<2<<endl;
				continue;
			}
		}

		if(tz.begin()->first!=0){
			ans++;
			if(a[0]==0)ans++;
		}
		if(tz.rbegin()->second!=n){
			ans++;
			if(a[n-1]==0)ans++;
		}
		cout<<ans<<endl;
	}

	return 0;
}
