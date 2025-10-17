#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i ,m, n) for (ll i = m; i <= n; ++i)

int main() {
	ll s;
	cin>>s;
	s*=4;
	vl yakusuu;
	loop(i,1,s){
		if(s%i==0)yakusuu.push_back(i);
	}
	ll ans=0;
	for(const auto apc:yakusuu){
		for(const auto cma:yakusuu){
			//大小関係崩れたらbreak;
			if(cma==apc)break;

			//偶奇が一緒ならスキップ
			if((cma%2)==(apc%2))continue;

			//Sの約数じゃなくなってもスキップ
			ll tmp1=cma*apc;
			if(s%tmp1!=0)continue;
			
			for(const auto dmb:yakusuu){
				//約数の確認
				ll tmp2=tmp1*dmb;
				if(s%tmp2!=0)continue;

				//大小関係の確認
				ll bpd=s/tmp2;
				if(dmb>=bpd)break;

				//偶奇の確認
				if((dmb%2)==(bpd%2))continue;
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}