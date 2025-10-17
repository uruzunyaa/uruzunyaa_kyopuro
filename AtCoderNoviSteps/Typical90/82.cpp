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
#define mod 1000000007LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

ll calc(ll r){
	ll ans=0;
	ll cnt=1;
	while(1){
		ll tmp=power(10,cnt-1)*9;
		ll shokou=power(10,cnt-1);
		ll makkou;
		if(r<tmp){
			makkou=shokou+r-1;
		}else{
			makkou=power(10,cnt)-1;
		}
		r-=makkou-shokou+1;
		
		ll spm=shokou+makkou;
		ll kousuu=makkou-shokou+1;
		if(spm%2==0)spm/=2;
		else kousuu/=2;

		spm%=mod;
		kousuu%=mod;

		ans+=((spm*kousuu)%mod)*cnt;
		ans%=mod;

		if(r==0)break;
		cnt++;
	}

	return ans;
}

//メイン
int main(){
	ll l,r;
	cin>>l>>r;
	l--;
	
	cout<<(mod+calc(r)-calc(l))%mod<<endl;
	return 0;
}
