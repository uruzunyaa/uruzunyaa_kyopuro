#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define eachdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353

//メイン
int main(){
	ll t;
	cin>>t;
	//if(t!=1)return 1;
	rep(z,t){
		string s;
		cin>>s;
		ll cntB=0;
		rep(i,s.size())if(s[i]=='B')cntB++;
		//Bの数が少ない時、全てのBが消える。
		if(cntB*3<s.size()){
			cout<<cntB<<endl;
			continue;
		}

		ll ans=0;
		deque<ll> d;

		ll i=0;
		loop(y,0,cntB){
			//Bを区切りとしてAの個数の列にする。
			ll cnt=0;
			while(s[i]=='A'&&i!=s.size()){
				cnt++;
				i++;
			}
			d.push_back(cnt);
			while(d.size()>=1){
				if(d.back()==2)d.pop_back(),ans++;
				if(d.size()<=1)break;
				if(d.at(d.size()-1)==0||d.at(d.size()-2)==0)break;
				if(d.at(d.size()-1)==1&&d.at(d.size()-2)==1)break;
				d.at(d.size()-2)+=d.back()-2;
				d.pop_back();
				ans++;
			}
			i++;
		}
		while(d.size()!=0&&d.front()==0)d.pop_front();
		while(d.size()!=0&&d.back()==0)d.pop_back();
		if(d.size()==0){
			cout<<ans<<endl;
			continue;
		}

		//dp[j][k]=j番目の数字
		unordered_map<ll,ll> dp;

		dp[0]=0;
		ll baseCost=0;

		//j個全て選んだ場合との差分で管理する。
		rep(j,d.size()){
			if(d.at(j)==0){
				//存在しないものを弾く
				if(!dp.count(baseCost+2))dp[baseCost+2]=-inf;
				if(dp.count(baseCost+1))dp[baseCost+2]=max(dp[baseCost+2],dp[baseCost+1]-1);
				if(dp.count(baseCost))dp[baseCost+2]=max(dp[baseCost+2],dp[baseCost]-1);
				baseCost+=2;
			}else if(d.at(j)==1){
				if(!dp.count(baseCost+1))dp[baseCost+1]=-inf;
				if(dp.count(baseCost))dp[baseCost+1]=max(dp[baseCost+1],dp[baseCost]-1);
				baseCost+=1;
			}else{
				baseCost+=2-d.at(j);
			}
		}
		ll mx=0;
		for(const auto val:dp){
			if(val.first-baseCost>=0)mx=max(mx,(val.first-baseCost)/2+val.second+(ll)d.size());
		}

		cout<<ans+mx<<endl;
	}
	return 0;
}
