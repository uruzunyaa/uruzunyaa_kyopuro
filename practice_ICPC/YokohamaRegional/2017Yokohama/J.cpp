#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

vl y,h,mds;

ll dfs(ll x){
	ll i = upper_bound(y.begin(),y.end(),x)-y.begin()-1;
	ll tmp = x-y[i];
	tmp %= mds[i];
	if(h[i]==-1)return x;
	return dfs(h[i]+tmp);
}

int main(){
    ll n,a,b,q;
	cin>>n>>a>>b>>q;
	vl x(a);
	string c(a,'.');
	rep(i,a)cin>>x[i]>>c[i],x[i]--;

	y=vl(b+2,0);
	h=vl(b+1,-1);
	y[b+1]=n;

	loop(i,1,b)cin>>y[i]>>h[i],y[i]--,h[i]--;

	mds=vl(b+1);
	rep(i,b+1){
		mds[i]=y[i+1]-y[i];
		if(h[i]!=-1){
			mds[i]=min(mds[i],y[i]-h[i]);
		}
		//cout<<mds[i]<<endl;
	}

	map<ll,char> ans;

	rep(i,a){
		ans[dfs(x[i])]=c[i];
	}


	while(q--){
		ll z;
		cin>>z;
		z--;
		ll tmp=dfs(z);
		if(ans.count(tmp))cout<<ans[tmp];
		else cout<<"?";
	}
	cout<<endl;
    return 0;
}