#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353LL

//nCrのmod mのテーブルを生成する。m非素数用
vvl pascal_list;
vvl make_pascal(ll n,ll k,ll m){
	pascal_list=vvl(n+1,vl(k+1,0));
	rep(i,n+1)pascal_list[i][0] = 1%m;
	rep(i,k+1)pascal_list[i][i] = 1%m;
	loop (i,1,n){
		loop (j,1,min(i-1,k)) {
			//nCr= n-1Cr-1 + n-1Cr
			pascal_list[i][j] = pascal_list[i-1][j-1] + pascal_list[i-1][j];
			pascal_list[i][j] %= m;
		}
	}
	return pascal_list;
}

//先にmake_pascalする
ll ncr_pascal(ll n,ll r){
	return pascal_list[n][r];
}

//メイン
int main(){
	//make_pascal(maxn,maxk,m);で作る
	//ncr_pascalで呼ぶ
	return 0;
}
