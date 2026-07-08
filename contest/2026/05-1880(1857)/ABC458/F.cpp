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

bool isprefix(vector<string> & s,string t){
	rep(i,s.size()){
		if(s.size()<t.size())continue;
		bool f=true;
		rep(j,t.size()){
			if(s[i][j]!=t[j]){
				f=false;
				break;
			}
		}
		if(f)return true;
	}
	return false;
}

//行列累乗前提関数
vvl matrix_mul_md(vvl a,vvl b,ll md){
	//a,bが全て同一値の正方行列である事を前提とする
	ll n = a.size();
    vvl ans(n, vl(n, 0));
    rep(i, n){
        rep(j, n){
            ll sum = 0;
            rep(k, n){
                sum += a[i][k] * b[k][j];
				sum%=md;
            }
            ans[i][j] = sum;
        }
    }
    return ans;
}

// 行列aのk乗をmで割った余りを計算
vvl matrix_pow(vvl a, ll k,ll md){
	ll n=a.size();
	vvl ans(n,vl(n,0));
	rep(i,n)ans[i][i]=1;
	while (k > 0){
		if ((k&1) ==1)ans=matrix_mul_md(ans,a,md);
		a=matrix_mul_md(a,a,md);
		k >>= 1;
	}
	return ans;
}

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	map<string,ll> taiou;
	string zeromozi;
	taiou[zeromozi]=0;
	ll cnt=1;
	set<ll> ng;
	rep(z,k){
		string s;
		cin>>s;
		string tmp;
		rep(i,s.size()){
			tmp.push_back(s[i]);
			if(taiou.count(tmp))continue;
			taiou[tmp]=cnt;
			cnt++;
		}
		ng.insert(taiou[s]);
	}

	for(const auto &val:taiou){
		string s=val.first;
		ll node=val.second;
		rep(i,s.size()){
			rep(j,i+1){
				string tmp;
				loop(z,j,i)tmp.push_back(s[z]);
				if(taiou.count(tmp)){
					if(ng.count(taiou[tmp])){
						ng.insert(node);
					}
				}
			}
		}
	}

	vvl mat(cnt,vl(cnt,0));
	for(const auto &val:taiou){
		string s=val.first;
		ll node=val.second;
		if(ng.count(node))continue;
		rep(i,26){
			string tmp=s;
			tmp.push_back('a'+i);
			if(taiou.count(tmp)){
				if(ng.count(taiou[tmp]))continue;
			}
			while(!taiou.count(tmp))tmp.erase(tmp.begin());
			mat[node][taiou[tmp]]++;
		}
	}
	vvl ans=matrix_pow(mat,n,mod);
	ll sums=0;
	rep(i,cnt){
		if(ng.count(i))continue;
		sums+=ans[0][i];
		sums%=mod;
	}
	sums%=mod;
	cout<<sums<<endl;
	return 0;
}
