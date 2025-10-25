#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL

ll solve(){
	ll a,b,x,y;
	cin>>a>>b>>x>>y;
	if(a==0&&b==0)return 1;
	ll bunbo=a*a+b*b;
	vl ans;
	loop(i,1,inf){
		if(x==0&&y==0)break;
		if(i>1000){
			cout<<-1<<endl;
			return 0;
		}
		
		//使わない場合
		ll nx=x*a+b*y;
		ll ny=a*y-b*x;
		if(nx%bunbo==0&&ny%bunbo==0){
			nx/=bunbo;
			ny/=bunbo;
			x=nx;
			y=ny;
			continue;
		}

		//使う場合
		x--;
		nx=x*a+b*y;
		ny=a*y-b*x;
		if(nx%bunbo==0&&ny%bunbo==0){
			nx/=bunbo;
			ny/=bunbo;
			x=nx;
			y=ny;
			ans.push_back(i);
			continue;
		}
		cout<<-1<<endl;
		return 0;
	}

	cout<<ans.size()<<endl;
	rep(i,ans.size()){
		cout<<ans[i]<<endl;
	}
	return 0;
}

int main() {
    while(solve()==0);
	return 0;
}