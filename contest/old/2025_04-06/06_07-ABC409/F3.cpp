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


ll manhat(ll x,ll y,ll a, ll b){
	return abs(x-a)+abs(y-b);
}

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl x(n),y(n);
	rep(i,n)cin>>x[i]>>y[i];
	priority_queue<pair<ll,pair<ll,ll>>> pq;

	rep(i,n)rep(j,i){
		pq.push({-manhat(x[i],y[i],x[j],y[j]),{i,j}});
	}
	UnionFind uf(n+q);
	while(q--){
		ll t;
		cin>>t;
		if(t==1){
			ll a,b;
			cin>>a>>b;
			rep(i,n){
				pq.push({-manhat(x[i],y[i],a,b),{i,n}});
			}
			x.push_back(a);
			y.push_back(b);
			n++;
		}else if(t==2){
			if(uf.size(0)==n){
				cout<<-1<<endl;
				continue;
			}
			
			bool f=true;
			ll num;
			do{
				num = pq.top().first;
				ll i = pq.top().second.first;
				ll j = pq.top().second.second;
				if(!uf.issame(i,j)){
					f=false;
					uf.unite(i,j);
				}
				pq.pop();
			}while(!pq.empty()&&(f||pq.top().first==num));
			cout<<-num<<endl;
		}else{
			ll u,v;
			cin>>u>>v;
			u--,v--;
			if(uf.issame(u,v))cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}
