#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,m;
	cin>>n>>m;
	ll aa;
	set<ll> a;
	rep(i,m)cin>>aa,a.insert(aa);
	vl ans;
	stack<ll> t;
	loop(i,1,n){
		if(a.count(i))t.push(i);
		else {
			ans.push_back(i);
			while(!t.empty()){
				ans.push_back(t.top());
				t.pop();
			}
		} 
	}
	rep(i,n)cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}