#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//隣接行列を渡すと、全対点を最適化する。(負の閉路があると壊れる)
void warshall_floyd(vvl & d){
	ll n=d.size();
	//kを経由する事で近くなるかを全ての点について調べる
	rep(k,n)rep(i,n)rep(j,n)d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}


//メイン
int main(){
	ll n,p,k;
	cin>>n>>p>>k;
	vvl a(n,vl(n));

	rep(i,n)rep(j,n)cin>>a[i][j];

	vvl wf=a;
	rep(i,n)rep(j,n)if(wf[i][j]==-1)wf[i][j]=p+1;
	warshall_floyd(wf);
	ll cnt=0;
	rep(i,n)rep(j,i){
		if(wf[i][j]<=p){
			cnt++;
		}
	}

	if(cnt>=k){
		if(cnt==k)cout<<"Infinity"<<endl;
		else cout<<0<<endl;
		return 0;
	}

	ll mn=0,mx=p;
	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;
		wf=a;
		rep(i,n)rep(j,n)if(wf[i][j]==-1)wf[i][j]=mid;
		warshall_floyd(wf);
		cnt=0;
		rep(i,n)rep(j,i){
			if(wf[i][j]<=p){
				cnt++;
			}
		}
		if(cnt>=k)mn=mid;
		else mx=mid-1;
	}
	ll ans=mn;
	mn=0,mx=p;
	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;
		wf=a;
		rep(i,n)rep(j,n)if(wf[i][j]==-1)wf[i][j]=mid;
		warshall_floyd(wf);
		cnt=0;
		rep(i,n)rep(j,i){
			if(wf[i][j]<=p){
				cnt++;
			}
		}
		if(cnt>=k+1)mn=mid;
		else mx=mid-1;
	}
	ans-=mn;
	cout<<ans<<endl;
	return 0;
}
