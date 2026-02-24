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

ll my_popcnt(ll n){
    ll count = 0;
    // xが0になるまでループ
    while (n > 0) {
        // x と 1 の論理積をとり、結果が1ならインクリメント
        if (n & 1) {
            count++;
        }
        // x を右に1ビットシフト
        n >>= 1;
    }
	return count;
}

void solve(){
	ll q,l,r;
	cin>>q>>l>>r;

	if(l%2==1&&r%2==0){
		bool f=false;
		ll rmn;
		rloop(b,60,1){
			if(((1LL<<b)&l)!=((1LL<<b)&r)){
				rloop(j,b-1,0){
					if(((1LL<<j)&l)!=((1LL<<j)&r)){
						if((1LL<<(j))&l){
							if(((1LL<<(j))&r)==0){
								f=true;
								rmn=r-(r%(1LL<<(b-1)));
							}
						}
						break;
					}
				}
				break;
			}
		}
		if(my_popcnt(l)%2==my_popcnt(r)%2){
			if(q==0)f=true;
		}
		if(f){
			if(q==0){
				ll ans=r-l+3;
				ans/=2;
				cout<<ans<<endl;
				return;
			}
			string ans;
			loop(i,l,rmn-1){
				if(my_popcnt(i)%2==my_popcnt(l)%2){
					ans.push_back('1');
				}else{
					ans.push_back('0');
				}
			}
			loop(i,rmn,r){
				if(my_popcnt(i)%2==my_popcnt(r)%2){
					ans.push_back('1');
				}else{
					ans.push_back('0');
				}
			}
			cout<<ans<<endl;
			return;
		}
	}
	if(q==0){
		ll ans=r-l+2;
		ans/=2;
		cout<<ans<<endl;
		return;
	}
	string odd,even;
	ll oddcnt=0,evencnt=0;
	loop(i,l,r){
		if(my_popcnt(i)%2==0){
			even.push_back('1');
			evencnt++;
			odd.push_back('0');
		}else{
			odd.push_back('1');
			oddcnt++;
			even.push_back('0');
		}
	}
	if(oddcnt>evencnt){
		cout<<odd<<endl;
	}else{
		cout<<even<<endl;
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
