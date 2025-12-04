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

//xor基底を管理し、何番目の要素由来かを管理する。
struct XorBasisList {
	//基底のリスト
    vl basis;
	//基底のリストの構成方法
    vvl used;
	//基底外のリストの構成方法
	vvl flip;
	//全体サイズの最大値
    int n;

    XorBasisList(int n_) : n(n_) {}
	//xを追加、その際、bitsが1の所を使用しているとして追加
    void add(ll x, const vl& bits) {
        vl tmp = bits;
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) tmp[j] ^= used[i][j]; 
            }
        }
        if (x != 0) {
            basis.push_back(x);
            used.push_back(tmp);
        }else{
			flip.push_back(tmp);
		}
    }

	//作れるかとその構成方法を返す
    pair<bool, vl> represent(ll x) const {
        vl res(n, 0);
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) res[j] ^= used[i][j];
            }
        }
        return {x == 0, res};
    }
};


int main(){
	vl A = {3, 5, 7, 9};
    int n = A.size();

    XorBasisList xb(n);

	//i番目の要素を使用中にして、構成に追加してみる。
    for (int i = 0; i < n; ++i) {
		vl tmp(n,0);
		tmp[i]=1;
        xb.add(A[i], tmp);
    }

	//値kの構成方法を知る。
	ll k= 15;
	auto [b,v]=xb.represent(k);
	if(b){
		vdbg(v);
	}else{
		cout<<"muri"<<endl;
	}
}