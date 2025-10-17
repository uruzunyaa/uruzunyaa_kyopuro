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
	ll n;
	cin>>n;
	vl p(n);
	rep(i,n)cin>>p[i];

	ll tmp=inf;
	vl st;
	rep(i,n){
		if(p.back()<tmp){
			st.push_back(p.back());
			tmp=p.back();
			p.pop_back();
		}else{
			st.push_back(p.back());
			tmp=p.back();
			p.pop_back();
			break;
		}
	}
	sort(st.rbegin(),st.rend());
	rep(i,st.size()){
		if(st[i]<tmp){
			p.push_back(st[i]);
			st.erase(st.begin()+i);
			break;
		}
	}
	rep(i,st.size()){
		p.push_back(st[i]);
	}
	vdbg(p);
	return 0;
}
