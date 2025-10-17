#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n)for(ll i;i<(ll)n;i++)

ll solve(){
	ll l,r,k;
	cin>>l>>r>>k;
	ll now=0;
	for(ll i=1;i*i<=r;i++){
		ll tmp=r/i;
		tmp*=i;
		if(tmp<l)k--;
		now=i;
		if(k==0){
			cout<<now<<endl;
			return 0;
		}
	}
	//デバッグ
	//cout<<k<<endl;
	ll rtr=now;
	for(ll i=rtr;i>0;i--){
		ll mx=r;
		ll mn=now;
		//i倍してL未満になるものの数を求める。
		while(mn!=mx){
			ll mid=(mn+mx+1)/2;
			if(mid*i<l&&mid-now<=k)mn=mid;
			else mx=mid-1;
		}
		k-=mn-now;
		now=mn;
		if(k==0){
			cout<<now<<endl;
			return 0;
		}
		
		//i倍してRをギリ超えない場所を求め、次回のminを更新。
		mn=now,mx=r;
		while(mn!=mx){
			ll mid=(mn+mx+1)/2;
			if(mid*i<=r)mn=mid;
			else mx=mid-1;
		}
		now=mn;
	}
	cout<<now+k<<endl;
	return 0;
}

int main() {
	ll q;
	cin>>q;	
	rep(i,q)solve();
}