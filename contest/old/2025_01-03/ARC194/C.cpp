#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


vl ab11,ab01,ab10;
ll sum=0;

ll f(ll cnt){
	priority_queue<pair<ll,bool>> one;
	rep(i,cnt)one.push({ab11[i],true});
	rep(i,ab10.size())one.push({ab10[i],false});
	
	ll tmp=sum;
	ll ans=0;
	priority_queue<ll> zero;
	rep(i,ab01.size())zero.push(-ab01[i]);
	while(!one.empty()){
		tmp-=one.top().first;
		if(one.top().second)zero.push(-one.top().first);
		one.pop();
		ans+=tmp;
	}
	while(!zero.empty()){
		tmp-=zero.top();
		zero.pop();
		ans+=tmp;
	}
	return ans;
}

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n),b(n);
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];
	
	
	rep(i,n){
		ll c;
		cin>>c;
		if(a[i]==1&&b[i]==1)ab11.push_back(c);
		if(a[i]==0&&b[i]==1)ab01.push_back(c);
		if(a[i]==1&&b[i]==0)ab10.push_back(c);
		if(a[i]==1)sum+=c;
	}
	sort(ab11.rbegin(),ab11.rend());
	ll mn=0;
	ll mx=ab11.size();

	ll ans=inf;
	while(mn!=mx){
		ll mid1=(mn+mn)/2;
		ll mid2=mid1+1;
		ll small=f(mid1);
		ll big=f(mid2);
		ans=min(ans,min(small,big));
		
		//坂が上がり気味
		if(small<big){
			mx=mid1;
		}

		if(small>big){
			mn=mid2;
		}

		if(small==big){
			mn=mid1;
			mx=mid1;
		}
	}
	// loop(i,max(mn-10,0LL),min(mn+10,(ll)ab11.size()-1LL)){
	// 	ans=min(ans,f(i));
	// }
	cout<<ans<<endl;
	return 0;
}
