#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vl>

struct CuttingFind{
	vector<int> par,siz;
	CuttingFind(int n):par(n,-1),siz(n,1){}
	int root (int x){
		if(par[x]==-1)return x;
		else return root(par[x]);
	}
	bool issame(int x,int y){
		return root(x) == root(y);
	}

	//根同士で連結しろ
	bool unite(int x,int y){
		if(issame(x,y)||par[x]!=-1||par[y]!=-1){
			cout<<"error"<<endl;
			return false;
		}
		if(siz[x]<siz[y])swap(x,y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	bool separate(int x,int y){
		if(par[y] == -1)swap(x,y);
		if(par[y] != x || par[x] != -1){
			cout<<"error2"<<endl;
			return false;
		}
		siz[x] -= siz[y];
		par[y] = -1;
		return true;
	}
	int size(int x){
		return siz[root(x)];
	}
};

int main() {
    
}