//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

struct XorBasis {
    vector<ll> basis;
    vector<vl> used;
	vvl flip;
    int n;

    XorBasis(int n_) : n(n_) {}

    void add(ll x, const vl& bits) {
        vl tmp = bits;
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) tmp[j] ^= used[i][j]; 
            }
        }
        if (x != 0) {
            basis.push_back(x);
            used.push_back(tmp);
        }else{
			flip.push_back(tmp);
		}
    }

    pair<bool, vl> represent(ll x) const {
        vl res(n, 0);
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) res[j] ^= used[i][j];
            }
        }
        return {x == 0, res};
    }
};

void solve() {
    ll n,k;
	cin>>n>>k;
	vl a(n);
	rep(i,n)cin>>a[i];

    XorBasis xb(n);
    for (int i = 0; i < n; ++i) {
        vl bits(n, 0);
        bits[i] = 1;
        xb.add(a[i], bits);
    }

    // 判定したい値
    auto [ok, used] = xb.represent(k);

    if (!ok){
        cout<<"No"<<endl;
		return;
    }

	if(k==a[0]){
		cout<<"Yes"<<endl;
		cout<<0<<endl<<endl;
		return;
	}
	
	ll siz=xb.flip.size();
	ll flips=0;
	while(1){
		vl ans;
		ll okind=inf;
		rrep(i,n-1){
			if(used[i]==used[i+1]){
				if(used[i]==0){
					ans.push_back(i);
					ans.push_back(i);
					
					//j番目の1を前に持ってくる動作
					for(ll j=i+2;j<n;j+=2){
						//それより前をお掃除
						for(ll l=i+2;l<j;l+=2){
							ans.push_back(l);
							ans.push_back(l);
						}
						for(ll l=j-1;l>i;l--){
							ans.push_back(l);
						}
					}
					ans.push_back(i);
					okind=i;
					break;
				}else{
					ans.push_back(i);
					
					if(i==n-2){
						okind=i;
						break;
					}
					i++;
					ans.push_back(i);
					ans.push_back(i);
					//j番目の1を前に持ってくる動作
					for(ll j=i+2;j<n;j+=2){
						//それより前をお掃除
						for(ll l=i+2;l<j;l+=2){
							ans.push_back(l);
							ans.push_back(l);
						}
						for(ll l=j-1;l>i;l--){
							ans.push_back(l);
						}
					}
					ans.push_back(i);
					ans.push_back(i-1);
					okind=i-1;
					break;
				}
			}
		}

		if(okind==inf){
			if(flips==siz)break;
			rep(i,n)used[i]^=xb.flip[flips][i];
			flips++;
			continue;
		}
		
		rrep(i,okind){
			if(used[i]==1){
				ans.push_back(i);
			}else{
				ans.push_back(i);
				ans.push_back(i);
				ans.push_back(i+1);
				ans.push_back(i);
			}
		}
		//出力
		cout<<"Yes"<<endl;
		rep(i,ans.size())ans[i]++;
		cout<<ans.size()<<endl;
		vdbg(ans);
		return;
	}
	cout<<"No"<<endl;
	return;
}

int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
}