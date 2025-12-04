#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

//分離可能UnionFind、経路圧縮をしない。
struct CuttingFind{
	vector<int> par, siz;
	CuttingFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	//根x と 根y のグループを併合する(お互い根ではない時、falseで何もしない)
	bool unite(int x, int y) {
		if (issame(x,y) || par[x] != -1 || par[y] != -1) {
			cout<<"error"<<endl;
			return false;
		}
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	//根の側から、その直系の子供を分離する。片方が根でもう片方が直系の子でなければならない。
	bool separate(int x,int y){
		if(par[y]==-1)swap(x,y);
		if(par[y]!=x||par[x]!=-1){
			cout<<"error2"<<endl;
			return false;
		}
		siz[x] -= siz[y];
		par[y]=-1;
		return true;
	}
	// x を含むグループのサイズを求める
	int size(int x) {
		return siz[root(x)];
	}
};

int main(){

	return 0;
}
