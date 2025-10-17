#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL
int main(){
	ll h,w;
	cin>>h>>w;
	vl b;
	vvl a(h,vl(w));
	rep(i,h)rep(j,w)cin>>a[i][j];
	h--,w--;
	rep(i,h)b.push_back(0);
	rep(i,w)b.push_back(1);

	

	ll ans=0;

	do{
		set <ll> k;
		k.insert(a[0][0]);
		bool f=true;
		ll x=0,y=0;
		rep(i,h+w){
			if(b[i]==0)x++;
			else y++;
			if(k.count(a[x][y]))f=false;
			k.insert(a[x][y]);
		}
		if(f)ans++;
	}while(next_permutation(b.begin(),b.end()));
	cout<<ans<<endl;
	return 0;
}