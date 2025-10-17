#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define vl vector<ll>
#define vvl vector<vvl>

int main(){
    string s;
	cin>>s;
	
	vl ansst={0};
	vl sums{0};
	map<ll,vl> mp;
	mp[0].push_back(0);

	rep(i,s.size()){
		if(s[i]=='('){
			ansst.push_back(ansst.back());
			sums.push_back(sums.back()+1);
			mp[sums.back()].push_back(sums.size()-1);
		}
		if(s[i]==')'){
			//累積和に追加
			sums.push_back(sums.back()-1);
			
			//1小さい奴のindex
			ll mind ;
			if(mp[sums.back()-1].size()==0)mind=0;
			else mind=mp[sums.back()-1].back();

			ll plus=mp[sums.back()].end()-lower_bound(mp[sums.back()].begin(),mp[sums.back()].end(),mind);
			ansst.push_back(ansst.back()+plus);

			//mapを更新
			mp[sums.back()].push_back(sums.size()-1);
		}
		if(s[i]=='-'){
			ansst.pop_back();
			mp[sums.back()].pop_back();
			sums.pop_back();
		}
		cout<<ansst.back()<<endl;
	}
}