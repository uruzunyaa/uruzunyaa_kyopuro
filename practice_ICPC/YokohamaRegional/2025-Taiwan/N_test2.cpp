#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl> 
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
#define rrep(i, n) for (ll i = n-1; i >= 0; --i)
constexpr ll INF = 9009009009009009009LL;

void test(ll m, ll n, vector<pair<ll, ll>> ans, ll k, ll b){
	vector<ll> u(n), v(n);
	rep(i, n){
		u[i] = ans[i].first;
		v[i] = ans[i].second;
		if(u[i] > m || v[i] > m){
			cout << "頂点番号がNを超えています\n";
			cout << m << " " << k << " " << b << endl;
			assert(false);
			return;
		}
		u[i]--;
		v[i]--;
	}

	ll k_cnt = 0;
	vector<vector<ll>> GG(m);
	rep(i, n){
		GG[u[i]].push_back(v[i]);
		GG[v[i]].push_back(u[i]);
	}
	rep(i, m){
		if(GG[i].size() % 2 == 1){
			k_cnt++;
		}
	}

	if(k_cnt != k){
		cout << "kの数が異なります"<<endl;
		cout << m << k << b << endl;
		cout<<k_cnt<<endl;
		assert(false);
		return;
	}

	ll b_cnt = 0;
	rep(i, n){
		vector<vector<ll>> G(m);
		vector<bool> ok(n, false);
		rep(j, n){
			if(i == j)continue;
			G[u[j]].push_back(v[j]);
			G[v[j]].push_back(u[j]);
		}
		queue<ll> q;
		q.push(0);
		ll cnt = 0;
		while(!q.empty()){
			ll now = q.front();
			q.pop();
			if(ok[now])continue;
			ok[now] = true;
			cnt++;
			for(ll next : G[now]){
				if(!ok[next]){
					q.push(next);
				}
			}
		}
		if(cnt != m){
			b_cnt++;
		}
	}
	if(b_cnt != b){
		cout << "Bの数が異なります\n";
		cout << m << k << b << endl;
		assert(false);
		return;
	}
}

void solve(ll n, ll k, ll b){
	//cin>>n>>k>>b;
	if(k%2==1){
		//cout<<"No"<<endl;
		return;
	}
	if(k<b&&k==0){
		//cout<<"No"<<endl;
		return;
	}
	if(n-2==b){
		//cout<<"No"<<endl;
		return;
	}
	if(n==3&&k==2&&b==0){
		//cout<<"No"<<endl;
		return;
	}
	if(n==4&&k==4&&b==1){
		//cout<<"No"<<endl;
		return;
	}
	//cout<<"Yes"<<endl;
	vector<pair<ll,ll>> ans;

	ll nbcnt=0;
	while(k<b){
		ans.push_back({n-2,n-1});
		ans.push_back({n-1,n});
		n-=2;
		b-=2;
		nbcnt+=2;
	}

	if(n-1==b){
		loop(i,2,n){
			ans.push_back({1,i});
		}
		//cout<<ans.size()<<endl;
		rep(i,ans.size()){
			//cout<<ans[i].first<<" "<<ans[i].second<<endl;
		}
		return;
	}

	if(n-3==b){
		ans.push_back({1,2});
		ans.push_back({1,3});
		ans.push_back({2,3});
		ll tmp=4;
		if(b+2<=k){
			tmp=6;
			ans.push_back({1,4});
			ans.push_back({2,5});
		}
		loop(i,tmp,n){
			ans.push_back({3,i});
		}

		//cout<<ans.size()<<endl;
		rep(i,ans.size()){
			//cout<<ans[i].first<<" "<<ans[i].second<<endl;
		}
	test(n+nbcnt, ans.size(), ans, k, b+nbcnt);
		return;
	}

	ll csize=n-b;
	loop(i,1,csize-1){
		ans.push_back({i,i+1});
	}
	ans.push_back({1,csize});

	loop(i,csize+1,n){
		ans.push_back({csize,i});
	}

	ll nokori=k-b;
	nokori/=2;

	loop(i,1,nokori){
		ans.push_back({i,i+(csize/2)});
	}

	//cout<<ans.size()<<endl;
	rep(i,ans.size()){
		//cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	test(n+nbcnt, ans.size(), ans, k, b+nbcnt);
	return;
}

int main(){
	ll t;
	//cin>>t;
	rep(n, 500){
		//cout << n << endl;
		rep(k, n+1){
			rep(b, n){
				solve(n, k, b);
				cout<<n<<k<<b<<endl;
			}
		}
	}

    //rep(i,t)solve();
}