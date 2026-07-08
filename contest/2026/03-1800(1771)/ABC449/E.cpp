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


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;



//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl a(n);
	vl bk(m+1,0);
	rep(i,n){
		cin>>a[i];
		bk[a[i]]++;
	}

	priority_queue<pair<ll,ll>> pq;
	loop(i,1,m){
		pq.push({-bk[i],-i});
	}

	ll q;
	cin>>q;
	vector<pair<ll,ll>> xi(q);
	rep(i,q){
		cin>>xi[i].first;
		xi[i].first--;
		xi[i].second=i;
	}
	sort(xi.begin(),xi.end());
	vl ans(q);

	ordered_set<ll> st;
	// order_of_key : x 未満である要素数を取得する
	// find_by_order : 0-indexed で k 番目に小さい値を指すイテレータを取得する
	// eraseの際、必ずイテレーターで消す事。
	ll xiindex=0;
	while(xiindex!=q&&xi[xiindex].first<n){
		ans[xi[xiindex].second] = a[xi[xiindex].first];
		xiindex++;
	}
	ll aindex=n;

	rep(i,n+1){
		while(!pq.empty()&&i==-pq.top().first){
			st.insert(-pq.top().second);
			pq.pop();
		}
		if(st.size()==m)break;
		while(xiindex!=q&&xi[xiindex].first<st.size()+aindex){
			ll tmp=xi[xiindex].first-aindex;
			ans[xi[xiindex].second]=*st.find_by_order(tmp);
			xiindex++;
		}
		aindex+=st.size();
	}

	while(xiindex!=q){
		ll tmp=xi[xiindex].first-aindex;
		tmp%=m;
		tmp++;
		ans[xi[xiindex].second]=tmp;
		xiindex++;
	}

	rep(i,q)cout<<ans[i]<<endl;
	return 0;
}
