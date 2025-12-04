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