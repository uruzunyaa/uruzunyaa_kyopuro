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


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}


//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

// Union-Find
struct UnionFind {
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	// x を含むグループと y を含むグループとを併合する
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false; 
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

void solve(){
	ll n;
	cin>>n;
	vl a(n),b(n);
	ll cnt=0,pos=0;
	vl oa,ob;
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];


	rep(i,n){
		if(a[i]==1){
			cnt++;
			pos+=i;
			oa.push_back(i+1);
		}
	}

	rep(i,n){
		if(b[i]==1){
			cnt--;
			pos-=i;
			ob.push_back(i+1);
		}
	}

	if(cnt!=0||pos!=0){
		cout<<"No"<<endl;
		return;
	}

	vvl ans;
	//{Aの座標,目標までの距離}
	deque<pair<ll,ll>> st;

	rep(i,oa.size()){
		pair<ll,ll> tmp={oa[i],ob[i]-oa[i]};
		if(tmp.second==0)continue;
		st.push_back(tmp);

		while(st.size()>=2){
			//最後尾が右移動なら後で
			if(st.back().second>0)break;

			//後から入れたのが左移動の時、右移動と相殺する。

			//左移動しか溜まってないなら終わり
			if(st.at(st.size()-2).second<0)break;

			ll movesiz=min(st.at(st.size()-2).second,-st.back().second);

			ans.push_back({st.at(st.size()-2).first,st.at(st.size()-2).first+movesiz,st.at(st.size()-1).first,st.at(st.size()-1).first-movesiz});
			st.at(st.size()-2).first+=movesiz;
			st.at(st.size()-2).second-=movesiz;
			st.at(st.size()-1).first-=movesiz;
			st.at(st.size()-1).second+=movesiz;

			if(st.at(st.size()-2).second==0){
				tmp=st.back();
				st.pop_back();
				st.pop_back();
				st.push_back(tmp);
			}
			if(st.back().second==0){
				st.pop_back();
			}
		}
	}

	//ここまででstが左移動の後に右移動の構図になっているはず

	while(st.size()!=0){

		ll movesiz=min(st.back().second,-st.front().second);

		//backは右移動、frontは左移動
		ans.push_back({st.front().first,st.front().first-movesiz,st.back().first,st.back().first+movesiz});
		st.back().first+=movesiz;
		st.back().second-=movesiz;
		st.front().first-=movesiz;
		st.front().second+=movesiz;

		
		if(st.back().second==0){
			st.pop_back();
		}
		if(st.front().second==0){
			st.pop_front();
		}
	}

	if(ans.size()>n/2){
		oa.clear();
		ob.clear();
		rep(i,n){
			if(a[i]==0){
				cnt++;
				pos+=i;
				oa.push_back(i+1);
			}
		}

		rep(i,n){
			if(b[i]==0){
				cnt--;
				pos-=i;
				ob.push_back(i+1);
			}
		}

		if(cnt!=0||pos!=0){
			cout<<"No"<<endl;
			return;
		}

		ans.clear();
		//{Aの座標,目標までの距離}
		st.clear();

		rep(i,oa.size()){
			pair<ll,ll> tmp={oa[i],ob[i]-oa[i]};
			if(tmp.second==0)continue;
			st.push_back(tmp);

			while(st.size()>=2){
				//最後尾が右移動なら後で
				if(st.back().second>0)break;

				//後から入れたのが左移動の時、右移動と相殺する。

				//左移動しか溜まってないなら終わり
				if(st.at(st.size()-2).second<0)break;

				ll movesiz=min(st.at(st.size()-2).second,-st.back().second);

				ans.push_back({st.at(st.size()-2).first,st.at(st.size()-2).first+movesiz,st.at(st.size()-1).first,st.at(st.size()-1).first-movesiz});
				st.at(st.size()-2).first+=movesiz;
				st.at(st.size()-2).second-=movesiz;
				st.at(st.size()-1).first-=movesiz;
				st.at(st.size()-1).second+=movesiz;

				if(st.at(st.size()-2).second==0){
					tmp=st.back();
					st.pop_back();
					st.pop_back();
					st.push_back(tmp);
				}
				if(st.back().second==0){
					st.pop_back();
				}
			}
		}

		//ここまででstが左移動の後に右移動の構図になっているはず

		while(st.size()!=0){

			ll movesiz=min(st.back().second,-st.front().second);

			//backは右移動、frontは左移動
			ans.push_back({st.front().first,st.front().first-movesiz,st.back().first,st.back().first+movesiz});
			st.back().first+=movesiz;
			st.back().second-=movesiz;
			st.front().first-=movesiz;
			st.front().second+=movesiz;

			
			if(st.back().second==0){
				st.pop_back();
			}
			if(st.front().second==0){
				st.pop_front();
			}
		}
	}

	rep(i,ans.size()){
		sort(ans[i].begin(),ans[i].end());
	}
	cout<<"Yes"<<endl;
	cout<<ans.size()<<endl;
	vvdbg(ans);
	
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
