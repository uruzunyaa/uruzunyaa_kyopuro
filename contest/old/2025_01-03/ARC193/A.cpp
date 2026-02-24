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
#define inf 1000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL


int main(){
    ll n;
	cin>>n;
	vl w(n),l(n),r(n);
	rep(i,n)cin>>w[i];
	vvl lw,rw;
	rep(i,n){
		cin>>l[i]>>r[i];
		l[i]--,r[i]--;
		rw.push_back({r[i],w[i]});
		lw.push_back({l[i],w[i]});
	}
	sort(rw.begin(),rw.end());
	sort(lw.rbegin(),lw.rend());

	vl rmn(2*n,inf),lmn(2*n,inf);

	ll mn=inf;
	ll ind=0;
	rep(i,2*n){
		while(ind<n&&rw[ind][0]<i){
			mn=min(mn,rw[ind][1]);
			ind++;
		}
		rmn[i]=mn;
	}

	mn=inf;
	ind=0;
	for(ll i=2*n-1;i>=0;i--){
		while(ind<n&&lw[ind][0]>i){
			mn=min(mn,lw[ind][1]);
			ind++;
		}
		lmn[i]=mn;
	}

	ll q;
	cin>>q;

	while(q--){
		ll s,t;
		cin>>s>>t;
		s--,t--;
		//直接移動可能な場合
		if(r[t]<l[s]||r[s]<l[t]){
			cout<<w[s]+w[t]<<endl;
			//cout<<"test"<<endl;
			continue;
		}
		ll ans=inf;
		//sとtの範囲外左側に一回飛んでから1回で戻る
		ans=min(ans,rmn[min(l[s],l[t])]);
		//sとtの範囲外右側に一回飛んでから1回で戻る
		ans=min(ans,lmn[max(r[s],r[t])]);

		//sの左行ってからtの右側へ
		ans=min(ans,rmn[l[s]]+lmn[r[t]]);
		//sの右行ってからtの左側へ
		ans=min(ans,lmn[r[s]]+rmn[l[t]]);

		ans+=w[s]+w[t];
		if(ans>inf)cout<<-1<<endl;
		else cout<<ans<<endl;
	}

}