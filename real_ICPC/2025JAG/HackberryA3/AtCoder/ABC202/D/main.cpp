// #辞書順 #組み合わせ
// aをA個、bをB個並べたとき、辞書順でK番目の文字列を求める
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

vector<vector<ll>> C(61, vector<ll>(61, 0));
ll comb(ll n, ll r){
	if(C[n][r] != 0) return C[n][r];
	if(r == 0 || n == r) return 1;
	return C[n][r] = comb(n - 1, r - 1) + comb(n - 1, r);
}

string f(ll A, ll B, ll K)
{
	if(A == 0) return string(B, 'b');
	if(B == 0) return string(A, 'a');

	ll an = comb(A - 1 + B, A - 1);
	if(K <= an) {
		return "a" + f(A - 1, B, K);
	} else {
		return "b" + f(A, B - 1, K - an);
	}
}

int main() {
	/*
	aabb
	abab
	abba
	baab
	baba
	bbaa

	aを選んだとき a=1, b=2
	bを選んだとき a=2, b=1
	3! / 1! * 2! = 3通り
	3! / 2! * 1! = 3通り

	b->aを選んだとき a=1, b=1
	b->bを選んだとき a=2, b=0
	2! / 1! * 1! = 2通り
	2! / 2! * 0! = 1通り
	*/

	ll A, B, K;
	cin >> A >> B >> K;

	cout << f(A, B, K) << endl;

	return 0;
}
