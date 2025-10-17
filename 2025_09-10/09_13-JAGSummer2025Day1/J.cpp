#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(ll i=0;i<n;i++)
#define loop(i,m,n) for(ll i=m;i<=n;i++)
#define ll long long

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
mt19937_64 mt64(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


ll rndnxt(ll mn,ll mx){
	ll range=mx-mn+1;
	return mn+(((mt64()%range)+range)%range);
}

int main(){
	vector<ll> sums={0};
	vector<vector<pair<ll,ll>>>g(66);
	rep(i,30){
		g[i+1].push_back({i+2,(1LL<<i)});
		g[i+2].push_back({i+1,(1LL<<i)});
		cout<<i+1<<" "<<i+2<<" "<<(1LL<<i)<<endl;
		sums.push_back(sums.back()+(1LL<<i));
	}
	loop(i,31,64){
		ll rd=rndnxt(1,1e9/33);
		cout<<i<<" "<<i+1<<" "<<rd<<endl;
		sums.push_back(sums.back()+rd);
	}

	ll q;
	cin>>q;

	while(q--){
		
	}
}