#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

ll n;
vl a;
vvl g;

vl ngcnt;
vector<vvl> ans;

void dfs(ll index,ll sum,vl & choice){
	if(index==n){
		if(sum==0)return;
		ans[sum].push_back(choice);

		if(ans[sum].size()==2){
			cout<<ans[sum][0].size()<<endl;
			vdbg(ans[sum][0]);
			cout<<ans[sum][1].size()<<endl;
			vdbg(ans[sum][1]);
			exit(0);
		}
		return;
	}

	//indexを選ばない場合
	dfs(index+1,sum,choice);

	//選ぶ場合
	if(ngcnt[index]==0){
		rep(i,g[index].size()){
			ngcnt[g[index][i]]++;
		}
		choice.push_back(index+1);

		dfs(index+1,sum+a[index],choice);

		choice.pop_back();
		
		rep(i,g[index].size()){
			ngcnt[g[index][i]]--;
		}
	}
	return;
}

//メイン
int main(){
	ll m;
	cin>>n>>m;
	a=vl(n);
	g=vvl(n);
	rep(i,n)cin>>a[i];

	rep(i,m){
		ll x,y;
		cin>>x>>y;
		x--,y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	ngcnt=vl(8889,0);
	ans=vector<vvl>(8889);
	vl tmp;
	dfs(0,0,tmp);
	return 0;
}
