#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll int
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
#define endl '\n'
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


ll n;

vector<bool> get_ok_list(vector<bool> &bllist,ll lens){
	vector<bool> ans=bllist;
	ll cnt=0;
	rep(i,n){
		if(bllist[i]){
			cnt++;
		}else{
			if(cnt<lens){
				loop(j,i-cnt,i-1)ans[j]=false;
			}
			cnt=0;
		}
	}
	if(cnt<lens){
		loop(j,n-cnt,n-1)ans[j]=false;
	}
	return ans;
}

pair<ll,ll> getlr(vector<bool> &bllist,ll lens,ll ind){
	ll l=ind;
	while(l>0){
		if(bllist[l-1]){
			l--;
		}else{
			break;
		}
	}
	l=max(l,ind-lens+1);
	return {l,l+lens-1};
}

void solve(){
	cin>>n;
	ll x[n],y[n],a[n],b[n];
	rep(i,n)cin>>x[i];
	rep(i,n)cin>>y[i];
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];

	vvl ans;

	bool big[n],small[n];
	rep(i,n){
		big[i]=false;
		small[i]=false;
	}

	
	vector<bool> canxi(n);
	vector<bool> canyi(n);
	rep(z,2*n){
		//chmax,x[i]を適応できるかチェック
		rep(i,n){
			rep(j,n){
				if(big[j]||x[i]<=b[j])canxi[j]=true;
				else canxi[j]=false;
			}
			canxi=get_ok_list(canxi,i+1);
			rep(j,n){
				if(!canxi[j])continue;
				ll val = j;
				if(small[val]==true)continue;
				if(x[i]==b[val]||(x[i]>b[val]&&big[val])){
					small[val]=true;
					pair<ll,ll> tmplr=getlr(canxi,(ll)(i+1),val);
					ans.push_back({0,(ll)(tmplr.first+1),(ll)(tmplr.second+1)});
					continue;
				}
			}
		}

		//y[i]
		rep(i,n){
			rep(j,n){
				if(small[j]||y[i]>=b[j])canyi[j]=true;
				else canyi[j]=false;
			}
			canyi=get_ok_list(canyi,i+1);
			rep(j,n){
				if(!canyi[j])continue;
				ll val = j;
				if(big[val]==true)continue;
				if(y[i]==b[val]||(y[i]<b[val]&&small[val])){
					big[val]=true;
					pair<ll,ll> tmplr=getlr(canyi,(ll)(i+1),val);
					ans.push_back({1,(ll)(tmplr.first+1),(ll)(tmplr.second+1)});
					continue;
				}
			}
		}
	}

	//行けるか判定
	rep(i,n){
		if(a[i]>b[i]){
			if(!big[i]){
				cout<<-1<<endl;
				return;
			}
		}else if(a[i]<b[i]){
			if(!small[i]){
				cout<<-1<<endl;
				return;
			}
		}
	}

	reverse(ans.begin(),ans.end());

	cout<<ans.size()<<endl;
	rep(i,ans.size()){
		if(ans[i][0]==0)cout<<"chmax ";
		else cout<<"chmin ";

		cout<<ans[i][1]<<" "<<ans[i][2]<<endl;
	}
	return;
}

//メイン
int main(){
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
