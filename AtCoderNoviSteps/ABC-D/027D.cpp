#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
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

//メイン
int main(){
	string s;
	cin>>s;

	ll score=0;
	vl list;
	rrep(i,s.size()){
		if(s[i]=='M')list.push_back(score);
		else if(s[i]=='+')score++;
		else score--;
	}

	sort(list.begin(),list.end());

	ll ans=0;
	rep(i,list.size()){
		if(i<list.size()/2)ans-=list[i];
		else ans+=list[i];
	}

	cout<<ans<<endl;
	return 0;
}
