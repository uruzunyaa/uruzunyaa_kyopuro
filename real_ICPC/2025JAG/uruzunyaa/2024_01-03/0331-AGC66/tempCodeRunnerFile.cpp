#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
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
		//if(s.size()>19)return 1;
		deque<pair<char,ll>> d;
		ll ans=0;
		ll i=0;
		while(i!=s.size()){
			//ランレングス圧縮
			ll cnt=1;
			while(i!=s.size()-1&&s[i]==s[i+1]){
				cnt++;
				i++;
			}
			d.push_back({s[i],cnt});

			while(1){
				if(d.size()<=1)break;
				//同じアルファベットの結合
				if(d.back().first==d.at(d.size()-2).first){
					d.at(d.size()-2).second+=d.back().second;
					d.pop_back();
				}
				if(d.size()<=1)break;

				if(d.back().first=='B'){
					if(d.at(d.size()-2).second==1){
						break;
					}else if(d.at(d.size()-2).second==0){
						d.at(d.size()-2)=d.back();
						d.pop_back();
					}else if(d.at(d.size()-2).second>d.back().second*2){
						ans+=d.back().second;
						d.at(d.size()-2).second-=d.back().second*2;
						d.pop_back();
					}else if(d.at(d.size()-2).second==d.back().second*2){
						ans+=d.back().second;
						d.pop_back();
						d.pop_back();
					}else{
						ll tmp = d.at(d.size()-2).second/2;
						ans+=tmp;
						d.at(d.size()-2).second-=tmp*2;
						d.back().second-=tmp;
					}
				}else{
					//先頭にBの時、前にAが無いので保留にすべき
					if(d.size()==2)break;

					if(d.back().second>=d.at(d.size()-2).second*2+1){
						ll tmp=d.at(d.size()-2).second;
						ans+=tmp;
						d.at(d.size()-2)={'A',d.back().second-tmp*2};
						d.pop_back();
					}else{
						break;
					}
				}
			}
			i++;
		}
		//cout<<ans<<endl;
		if(d.size()>=2&&d.back().first=='A'){
			ans+=min(d.back().second/2,d.at(d.size()-2).second);
		}
		cout<<ans<<endl;
	}
	return 0;
}
