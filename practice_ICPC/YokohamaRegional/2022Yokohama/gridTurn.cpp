#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//グリッドを右に90度回転する。
vector<string> gridTurn(vector<string> &s){
	ll h=s[0].size();
	ll w=s.size();
	vector<string> res(h,string(w,'.'));

	rep(i,h)rep(j,w){
		res[i][j]=s[w-j-1][i];
	}

	return res;
}

int main(){

	return 0;
}
