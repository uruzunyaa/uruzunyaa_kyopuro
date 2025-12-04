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
template <typename T>
struct offset_vector {
    vector<T> data;
    const int offset;

    /** @brief 負のインデックスをサポートするベクトル
     * @param n 正のインデックスのサイズ
     * @param offset 負のインデックスに拡張する数
     * @param init_val 初期値（デフォルトはT()）
     */
    offset_vector(int n, int offset = 0, T init_val = T()) : offset(offset) {
        assert(0 <= n && "offset_vectorの初期化時のnは0以上でなければなりません");
        assert(0 <= offset && "offset_vectorの初期化時のoffsetは0以上でなければなりません");
        data.resize(n + offset, init_val);
    }

    T& operator[](int i) {
        assert(0 <= i + offset && "offset_vectorへの負方向の範囲外参照です");
        assert(i + offset < data.size() && "offset_vectorへの正方向の範囲外参照です");
        return data[i + offset];
    }

    auto begin() {
        return data.begin();
    }
    auto end() {
        return data.end();
    }
    auto rbegin() {
        return data.rbegin();
    }
    auto rend() {
        return data.rend();
    }
    auto size() const {
        return data.size();
    }
    size_t positive_size() const {
        return data.size() - offset;
    }
    auto empty() const {
        return data.empty();
    }
    auto front() {
        assert(!data.empty() && "offset_vectorが空です");
        return data.front();
    }
    auto back() {
        assert(!data.empty() && "offset_vectorが空です");
        return data.back();
    }

    void push_back(const T& value) {
        data.push_back(value);
    }
    void pop_back() {
        assert(offset < data.size() && "offset_vectorのpop_backは、負の要素に対しては使用できません");
        assert(!data.empty() && "offset_vectorのpop_backは、空のベクトルに対しては使用できません");
        data.pop_back();
    }

    friend ostream& operator<<(ostream& os, const offset_vector<T>& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i != 0) os << " ";
            os << v.data[i];
        }
        os << "\n";
        return os;
    }
};

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


ll solve(){
	ll n;
	cin>>n;
	if(n==0){return 1;}

	vl a(n);
	vl odd;
	vl even;
	ll allsum=0;
	rep(i,n){
		cin>>a[i];
		allsum+=a[i];
		if(a[i]%2==0)even.push_back(i);
		else odd.push_back(i);
	}

	if(odd.size()%2==1){
		cout<<"No"<<endl;
		return 0;
	}

	//1個でも偶数があればRotationで構築可能
	if(even.size()!=0){
		vl red(n);
		vl blue(n);
		while(even.size()>1){
			red[even.back()]=a[even.back()]/2;
			blue[even.back()]=a[even.back()]/2;
			even.pop_back();
		}
		odd.push_back(even[0]);

		vl abcd(odd.size());
		// abcd[0]を求める
		ll sums=0;
		rep(i,odd.size()){
			if(i%2==0){
				sums+=a[odd[i]];
			}else{
				sums-=a[odd[i]];
			}
		}
		abcd[0]=sums/2;
		rep(i,odd.size()-1){
			abcd[i+1]=a[odd[i]]-abcd[i];
		}

		rep(i,odd.size()){
			red[odd[i]]=abcd[i];
			blue[odd[i]]=abcd[(i+1)%odd.size()];
		}
		cout<<"Yes"<<endl;
		vdbg(red);
		vdbg(blue);
		return 0;
	}

	
	//奇数のみの場合
	vector<vector<offset_vector<pair<bool,bool>>>> dp(n+1,vector<offset_vector<pair<bool,bool>>>(n/2+1,offset_vector<pair<bool,bool>>(150*n+1,150*n,{false,false})));
	dp[0][0][0]={true,false};
	rep(i,n){
		rep(j,n/2){
			loop(k,-150*i,150*i){
				if(!dp[i][j][k].first)continue;

				//使わない場合
				dp[i+1][j][k]={true,false};

				//使う場合
				dp[i+1][j+1][k+a[i]]={true,true};
				
			}
		}
	}
	if(!dp[n][n/2][allsum/2].first){
		cout<<"No"<<endl;
		return 0;
	}

	vl g1;
	vl g2;
	ll nowj=n/2;
	ll nowk=allsum/2;
	rrep(i,n){
		if(dp[i+1][nowj][nowk].second){
			nowj--;
			nowk-=a[i];
			g1.push_back(i);
		}else{
			g2.push_back(i);
		}
	}
	//vdbg(g1);
	//vdbg(g2);

	vl red(n);
	vl blue(n);
	vl abcd(n);
	abcd[0]=0;

	rep(i,n-1){
		if(i%2==0){
			abcd[i+1]=a[g1[i/2]]-abcd[i];
		}else{
			abcd[i+1]=a[g2[i/2]]-abcd[i];
		}
	}

	rep(i,n){
		if(i%2==0){
			red[g1[i/2]]=abcd[i];
			blue[g1[i/2]]=abcd[(i+1)%n];
		}else{
			red[g2[i/2]]=abcd[i];
			blue[g2[i/2]]=abcd[(i+1)%n];
		}
	}
	cout<<"Yes"<<endl;
	vdbg(red);
	vdbg(blue);

	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
