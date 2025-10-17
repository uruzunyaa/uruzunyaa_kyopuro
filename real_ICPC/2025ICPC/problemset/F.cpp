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
	ll n;
	cin>>n;
	if(n==0){return 1;}
	string s,t;
	cin>>s>>t;

	if(s==t){
		cout<<"yes"<<endl;
		cout<<endl;
		return 0;
	}

	ll cnta=0,cntb=0;
	rep(i,n){
		if(s[i]=='a')cnta++;
		else cntb++;
	}

	ll cnta2=0,cntb2=0;
	rep(i,n){
		if(t[i]=='a')cnta2++;
		else cntb2++;
	}

	if(cnta!=cnta2){
		cout<<"no"<<endl;
		return 0;
	}

	string ans;
	
	//前にaを全部持ってくる
	rep(i,n){
		if(s[i]=='b'){
			rep(j,cnta-i)ans.push_back('B');
			break;
		}
	}

	//末尾がbになるまで構成する。
	rep(i,n){
		if(t[n-i-1]=='b'){
			if(i==0)break;
			rep(j,cntb){
				ans.push_back('A');
			}
			cnta-=i;
			rep(j,cnta){
				ans.push_back('B');
			}
			n-=i;
			break;
		}
	}

	while(cnta!=0){
		//末尾のBの個数を数える。
		rep(i,n){
			if(t[n-i-1]=='a'){
				cntb-=i;
				rep(j,cntb){
					ans.push_back('A');
				}
				n-=i;
				break;
			}
		}
		if(cntb==0)break;

		//末尾のAの個数を数える。
		rep(i,n){
			if(t[n-i-1]=='b'){
				cnta-=i;
				rep(j,cnta){
					ans.push_back('B');
				}
				n-=i;
				break;
			}
		}
		if(cnta==0)break;
	}
	cout<<"yes"<<endl;
	cout<<ans<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
