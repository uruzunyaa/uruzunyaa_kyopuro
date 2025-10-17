#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define um unordered_map
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){if(a[ii][jj]!=inf)cout<<setw(3)<<a[ii][jj]<<" ";else cout<<" -  ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

//メイン
int main(){
	string s;
	cin>>s;
	if(s.size()%2==1&&s.front()==s.back()){
		cout<<"Second"<<endl;
		return 0;
	}
	
	if(s.size()%2==0&&s.front()!=s.back()){
		cout<<"Second"<<endl;
		return 0;
	}

	cout<<"First"<<endl;
	return 0;
}
