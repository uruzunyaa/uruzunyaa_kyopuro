#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define inf 1000000000000000000LL

int main(){
    ll n;
	cin>>n;
	vl p(n),f(n);
	rep(i,n)cin>>p[i],p[i]--;
	rep(i,n)cin>>f[i],f[i]--;

	//周期,{~~の倍数,+何}
	vector<pair<ll,ll>> syuuki(n,{inf,inf});
	vl kiroku(n,inf);
	rep(i,n*3){
		rep(j,n){
			if(p[j]==j){
				if(kiroku[j]!=inf){
					ll tmp=(i-kiroku[j]);
					syuuki[j]={tmp,i%tmp};
				}
				kiroku[j]=i;
			}
		}
		vl tmp(n,0);
		rep(j,n)tmp[j]=p[f[j]];
		p=tmp;
	}

	//rep(i,n)cout<<syuuki[i].first<<endl;

	rep(i,n){
		if(syuuki[i].first==inf){
			cout<<-1<<endl;
			return 0;
		}
	}

	pair<ll,ll> ans={1,0};
	rep(i,n){
		ll nlcm=lcm(ans.first,syuuki[i].first);
		bool check=true;
		ll num=ans.second;
		rep(j,syuuki[i].first){
			if(num%syuuki[i].first==syuuki[i].second){
				check=false;
				break;
			}
			num+=ans.first;
		}
		if(check){
			cout<<-1<<endl;
			return 0;
		}
		ans={nlcm,num};
	}
	cout<<ans.second<<endl;
}