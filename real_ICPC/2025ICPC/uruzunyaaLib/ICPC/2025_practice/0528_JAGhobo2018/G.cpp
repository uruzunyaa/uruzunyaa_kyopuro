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
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int

//#include<atcoder/lazysegtree>

ll introot(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	ll ans=0;
	loop(i,max(0LL,sqrtN-2),sqrtN+2){
		if(i * i <= n)ans=i;
	}
	return ans;
}

template <typename T>
struct offset_vector {
    vector<T> data;
    const size_t offset;

    /** @brief 負のインデックスをサポートするベクトル
     * @param n 正のインデックスのサイズ
     * @param offset 負のインデックスに拡張する数
     * @param init_val 初期値（デフォルトはT()）
     */
    offset_vector(size_t n, size_t offset = 0, T init_val = T()) : offset(offset) {
        data.resize(n + offset, init_val);
    }

    T& operator[](size_t i) {
        assert(0 <= i + offset);
        assert(i + offset < data.size());
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
        assert(!data.empty());
        return data.front();
    }
    auto back() {
        assert(!data.empty());
        return data.back();
    }

    void push_back(const T& value) {
        data.push_back(value);
    }
    void pop_back() {
        assert(offset < data.size());
        assert(!data.empty());
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


ll solve(){
	int n,m;
	cin>>n>>m;
	if(n==0&&m==0){return 1;}
	
	vector<offset_vector<ll>> imos(4,offset_vector<ll>(n+32000,32000,0));
	rep(i,m-1){
		ll a,x;
		cin>>a>>x;
		ll rta=introot(a);
		imos[1][x-rta]+=a-rta*rta;
		imos[2][x-rta+1]+=rta*rta-(rta-1)*(rta-1);
		imos[3][x-rta+2]+=-2;
		imos[1][x+rta+1]+=rta*rta-a;
		imos[2][x+rta+1]+=rta*rta-(rta-1)*(rta-1);
		imos[3][x+rta+1]+=2;
	}

	rloop(i,3,1){
		imos[i][0]+=0;
		ll sum=0;
		loop(j,-32000,n){
			sum+=imos[i][j];
			imos[i-1][j]+=sum;
		}
	}

	vl cost(n);
	rep(i,n)cost[i]=imos[0][i+1];
	
	//vdbg(cost);
	ll a;
	cin>>a;
	ll mn=0,mx=1e14;

	while(mn!=mx){
		ll mid=(mn+mx+1)/2;
		//cout<<mid<<endl;
		ll l=0,r=n-1;
		rep(i,n){
			if(cost[i]>=mid)continue;
			if(cost[i]+a<mid){
				l=n;
				r=0;
				break;
			}
			ll husoku=mid-cost[i];
			//lに置いた時左過ぎたらlを加算
			while(l<i&&a-((l-i)*(l-i))<husoku)l++;
			//rも同様に右過ぎたらrを減算。
			while(r>i&&a-((r-i)*(r-i))<husoku)r--;
		}
		if(l>r)mx=mid-1;
		else mn=mid;
	}
	cout<<mn<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
