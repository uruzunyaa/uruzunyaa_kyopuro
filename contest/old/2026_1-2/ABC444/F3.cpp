//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//aをx以上を保って限界まで割る
vector<pair<ll,ll>> waru(ll x,ll a){
	//まず、境界は考えず大丈夫なとこまで割る
	ll two=1;
	while(a/(two*2)>=x)two*=2;
	vector<pair<ll,ll>> ans;
	ans.push_back({a/two,two-(a%two)});
	if(a%two!=0){
		ans.push_back({a/two+1,a%two});
	}

	//次に、境界丁度になるなら割る。
	rep(i,ans.size()){
		if(ans[i].first/2>=x){
			ans[i].first/=2;
			ans[i].second*=2;
		}else if((ans[i].first+1)/2>=x){
			ans[i].first++;
			ans[i].first/=2;
		}
	}
	return ans;
}

void solve(){
	ll n,m;
	cin>>n>>m;
	ll mxsum=0;
	vl a(n);
	rep(i,n)cin>>a[i],mxsum+=a[i];
	mxsum-=(m+n)/2;

	sort(a.rbegin(),a.rend());
	

	//答えとなる中央値でにぶたん
	ll mn=1,mx;
	//割る数側の限界的な、中央値の最大値を求める。
	rep(i,min((n+m+1)/2,n))mx=a[n-i-1];

	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;

		/*
		無理なのは、以下の2通り
		・割る数側が足りなくて、中央値以上の個数が確保できない時
		・中央値以上の個数を確保した後、他を全て1にしても合計が足りず分割が必要な時
		前者は先に求めている。
		よって、割る数は足りている前提で
		中央値以上の個数を確保し、その時の合計が大きすぎないか判定する。
		※デカい奴を分割して、中央値を切らないのは問題ではない
		　(それが起きても中央値が増加するだけなので)
		　なお、合計を小さくする必要がある時は切る回数過剰な場合なので
		　切る数不足の際に合計の最小化はしなくて良い(そんなケースはない)
		*/

		vector<pair<ll,ll>>list;
		rep(i,n){
			if(a[i]<mid)break;
			vector<pair<ll,ll>>tmp=waru(mid,a[i]);
			list.push_back(tmp[0]);
			if(tmp.size()==2){
				list.push_back(tmp[1]);
			}
		}
		sort(list.begin(),list.end());

		//個数が足りてるかと合計が超えてないか判定
		ll sums=0;
		ll cnt=0;
		for(auto &val:list){
			if(val.first<mid)continue;
			if(cnt+val.second<(n+m+1)/2){
				cnt+=val.second;
				sums+=val.first*val.second;
			}else{
				sums+=val.first*((n+m+1)/2-cnt);
				cnt=(n+m+1)/2;
				break;
			}
		}
		if(cnt<(n+m+1)/2||sums>mxsum)mx=mid-1;
		else mn=mid;
	}
	cout<<mx<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
