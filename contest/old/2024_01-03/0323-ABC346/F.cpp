#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353
//#define mod 1000000007

//メイン
int main(){
	ll n;
	string s,t;
	cin>>n>>s>>t;

	//各アルファベットの1周の数
	vvl index(26);
	rep(i,s.size()){
		index[s[i]-'a'].push_back(i);
	}

	ll l=0,r=inf;
	while(l!=r){
		ll mid=(l+r+1)/2;
		//何番目の文字を参照しているか。
		ll cnt=0;
		rep(i,t.size()){
			if(index[t[i]-'a'].size()==0){
				cnt=inf;
				break;
			}
			if(cnt>s.size()*n)break;
			ll nokori=mid;
			
			//今いるサイクル内の残りの文字数を数える。
			ll tmp=index[t[i]-'a'].end()-lower_bound(index[t[i]-'a'].begin(),index[t[i]-'a'].end(),cnt%s.size());

			cnt-=cnt%s.size();
			if(tmp<nokori){
				//次のサイクルにも文字が必要な場合、現在のサイクルの最後の文字の次に移動させる。
				cnt+=index[t[i]-'a'][index[t[i]-'a'].size()-1]+1;
				nokori-=tmp;
			}else{
				//次のサイクルがない場合、場所を確定して終了
				cnt+=index[t[i]-'a'][index[t[i]-'a'].size()-tmp+nokori-1]+1;
				continue;
			}

			//サイクル分スキップ。
			cnt+=(nokori/index[t[i]-'a'].size())*s.size();
			nokori%=index[t[i]-'a'].size();

			//次のサイクルがない場合、場所を確定して終了
			if(nokori==0)continue;
			cnt=((cnt-1)/s.size()+1)*s.size();
			cnt+=index[t[i]-'a'][nokori-1]+1;
		}

		//サイクル外判定
		if(cnt>s.size()*n)r=mid-1;
		else l=mid;
	}
	cout<<l<<endl;

	return 0;
}
