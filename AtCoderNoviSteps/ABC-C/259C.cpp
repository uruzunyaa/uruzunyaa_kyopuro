#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	string s,t;
	cin>>s>>t;
	vector<pair<char,ll>> rs,rt;
	rep(i,s.size()){
		if(i==0||rs.back().first!=s[i])rs.push_back({s[i],1});
		else rs.back().second++;
	}
	rep(i,t.size()){
		if(i==0||rt.back().first!=t[i])rt.push_back({t[i],1});
		else rt.back().second++;
	}

	if(rs.size()!=rt.size()){
		cout<<"No"<<endl;
		return 0;
	}

	rep(i,rs.size()){
		if(rs[i]==rt[i])continue;
		if(rs[i].first==rt[i].first&&rs[i].second>=2&&rt[i].second>rs[i].second)continue;
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;
	return 0;
}
