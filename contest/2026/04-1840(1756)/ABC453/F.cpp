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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>

ll tuika=-1;

ll dfs(ll node,vector<vector<pair<ll,ll>>> & cnt,priority_queue<pair<ll,ll>> & ans,vvl &childe,ll leader){
	if(leader!=-1){
		if(cnt[node].size()==0){
			childe[leader].push_back(node);
		}else{
			rep(i,cnt[node].size()){
				dfs(cnt[node][i].second,cnt,ans,childe,leader);
			}
		}
		return 0;
	}
	
	if(cnt[node].size()==0)return node;
	rrep(i,cnt[node].size()){
		if(i==0){
			if(tuika==-1)tuika=cnt[node][i].second;
			return dfs(cnt[node][i].second,cnt,ans,childe,-1);
		}
		ans.push(cnt[node][i]);
		dfs(cnt[node][i].second,cnt,ans,childe,cnt[node][i].second);
	}
	//ここまで来ないはず
	assert(-1);
	return inf;
}

ll dfscnt(ll node,ll mae,vvl &g,vector<vector<pair<ll,ll>>> & ans){
	for(const auto val:g[node]){
		if(val==mae)continue;
		ans[node].push_back({dfscnt(val,node,g,ans),val});
	}
	if(ans[node].size()==0)return 1;

	ll res=0;

	rep(i,ans[node].size()){
		res+=ans[node][i].first;
	}
	return res;
}

void solve(){
	tuika=-1;
	ll n,k;
	cin>>n>>k;
	vvl g(n);
	rep(i,n-1){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector<pair<ll,ll>> c(k);
	rep(i,k)cin>>c[i].first,c[i].second=i;
	sort(c.rbegin(),c.rend());

	//スタートする葉を決める
	ll st;
	rep(i,n){
		if(g[i].size()==1)st=i;
	}
	//DFSでそれぞれの部分木に対する葉の個数を求める
	vector<vector<pair<ll,ll>>> cnt(n);
	ll ollleaf=dfscnt(st,-1,g,cnt);
	ollleaf++;
	rep(i,n)sort(cnt[i].rbegin(),cnt[i].rend());

	//葉が多い方へ貪欲に行く1本のパスを取る。
	//その時に使わなかった集合の成分を管理
	priority_queue<pair<ll,ll>> list;
	vvl childe(n); 
	ll ed=dfs(st,cnt,list,childe,-1);
	list.push({0,tuika});
	childe[tuika].push_back(tuika);

	vl ans(n,-1);
	//listに分離した部分木達のリスト{頂点数,その根}のpriority_queue
	//childeに分離した部分木の根とそいつに付く葉のリストchilde[親のind][i番目の子供]
	if(c[0].first<=1){
		cout<<-1<<endl;
		return;
	}
	c[0].first-=2;
	ollleaf-=2;
	ans[st]=c[0].second;
	ans[ed]=c[0].second;
	
	//大きい物から2個を常に取る
	rep(i,k){
		if(ollleaf<=0)break;
		if(i!=0&&c[i].first<2){
			cout<<-1<<endl;
			return;
		}

		//2個ずつ割り当て
		while(c[i].first>=2&&list.size()>=2){
			c[i].first-=2;
			auto a = list.top();
			list.pop();
			auto b = list.top();
			list.pop();

			//色 c[i].second をa.secondの子とb.secondの子に塗る
			ans[childe[a.second].back()]=c[i].second;
			ans[childe[b.second].back()]=c[i].second;
			childe[a.second].pop_back();
			childe[b.second].pop_back();

			a.first--;
			b.first--;
			if(a.first>0)list.push(a);
			if(b.first>0)list.push(b);
			ollleaf-=2;
		}

		//余り1個があったら割り振り
		if(c[i].first==1&&!list.empty()){
			c[i].first--;
			auto a = list.top();
			list.pop();

			//色 c[i].second をa.secondの子に塗る
			ans[childe[a.second].back()]=c[i].second;
			childe[a.second].pop_back();

			a.first--;
			if(a.first>0)list.push(a);
			ollleaf--;
		}
	}

	vl nokori;
	rep(i,k){
		rep(z,c[i].first){
			if(nokori.size()==n)break;
			nokori.push_back(c[i].second);
		}
	}

	rep(i,n){
		if(ans[i]==-1){
			ans[i]=nokori.back();
			nokori.pop_back();
		}
		ans[i]++;
	}
	vdbg(ans);
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
