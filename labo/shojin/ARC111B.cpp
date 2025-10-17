//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL


//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n),b(n);
	vector<set<ll>> ind(400001);
	rep(i,n){
		cin>>a[i]>>b[i];
		ind[a[i]].insert(i);
		ind[b[i]].insert(i);
	}
	queue<ll> q;
	rep(i,400001){
		if(ind[i].size()==1)q.push(i);
	}
	ll ans=0;
	while(!q.empty()){
		ll num=q.front();
		q.pop();
		if(ind[num].size()==1){
			ans++;
			ll tmp = *ind[num].begin();
			ind[a[tmp]].erase(tmp);
			ind[b[tmp]].erase(tmp);
			if(ind[a[tmp]].size()==1)q.push(a[tmp]);
			if(ind[b[tmp]].size()==1)q.push(b[tmp]);
		}
	}
	rep(i,400001){
		if(ind[i].size()>=2)ans++;
	}
	cout<<ans<<endl;
	return 0;
}
