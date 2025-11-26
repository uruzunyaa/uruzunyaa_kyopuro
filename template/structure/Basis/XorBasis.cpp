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

//xor基底を求める、確認する。
struct XorBasis {
	//基底のリスト
    vl basis;

	//xを追加
    void add(ll x) {
        for (auto b : basis) {
            x=min(x,x^b);
        }
        if (x != 0) {
            basis.push_back(x);
		}
    }

    //xが含まれているか確認
	bool check(ll x){
       for (auto b : basis) {
            x=min(x,x^b);
        }
        return x==0;
    }
};


int main(){
	vl A = {3, 5, 6, 9};
    int n = A.size();

    XorBasis xb;

	//要素を追加。
    for (int i = 0; i < n; ++i) {
        xb.add(A[i]);
    }

	//値kが作れるかチェック。
	ll k= 1;
	auto b=xb.check(k);
	if(b){
		cout<<"ok"<<endl;
	}else{
		cout<<"muri"<<endl;
	}
}